/*
 *  Copyright (C) 2015 Fishstix - based upon GPL DosBox and anDosBox
 *  Copyright (C) 2011 Locnet (android.locnet@gmail.com)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#define USE_JNIGRAPHIC 1
#include <jni.h>
#if USE_JNIGRAPHIC
#include <android/bitmap.h>
#endif
#include "config.h"
#include "AndroidOSfunc.h"
#include "string.h"
#include "loader.h"
#include "util.h"
#include "SDL.h"
//#include "SDL_mouse.h"
#include "render.h"
#include "keyboard.h"
#include "keycodes.h"

#include <queue>

#include <android/log.h>
#define LOGD(LOG_TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGV(LOG_TAG, ...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGE(LOG_TAG, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOG_TAG "DosBoxTurbo"

std::queue<struct locnet_al_event> eventQueue;

struct loader_config myLoader;
struct loader_config *loadf;
bool	enableSound = true;
bool	enableCycleHack = true;
bool	enableRefreshHack = true;
bool	enableMixerHack = true;
bool	enableGlide = false;
int		mouseValid = 0;
//bool	enableAutoCPU = true;

//extern SDL_AudioCallback mixerCallBack;
extern void (SDLCALL *mixerCallBack)(void *userdata, Uint8 *stream, int len);

void Android_Exit();
char *Android_VideoGetBuffer();

JNIEnv	*gEnv = NULL;
jobject JavaCallbackThread = NULL;
jmethodID JavaVideoRedraw = NULL;
jmethodID JavaVideoSetMode = NULL;
jmethodID JavaAudioWriteBuffer = NULL;
jmethodID JavaAudioGetBuffer = NULL;
jmethodID JavaAudioInit = NULL;
jmethodID JavaExit = NULL;
jmethodID JavaAudioExit = NULL;
jclass JavaCallbackThreadClass = NULL;

//locnet, 2011-04-28, support 2.1 or below
jmethodID JavaVideoGetBuffer = NULL;

void Android_Init(JNIEnv * env, jobject obj, jobject bitmap, jint width, jint height) {
	gEnv = env;
	JavaCallbackThread = env->NewGlobalRef(obj);
	JavaCallbackThreadClass = env->GetObjectClass(JavaCallbackThread);

	JavaVideoRedraw = env->GetMethodID(JavaCallbackThreadClass, "callbackVideoRedraw", "(IIII)V");
	JavaVideoSetMode = env->GetMethodID(JavaCallbackThreadClass, "callbackVideoSetMode", "(II)Landroid/graphics/Bitmap;");
	JavaAudioInit = env->GetMethodID(JavaCallbackThreadClass, "callbackAudioInit", "(IIII)I");
	JavaAudioWriteBuffer = env->GetMethodID(JavaCallbackThreadClass, "callbackAudioWriteBuffer", "(I)V");
	JavaAudioGetBuffer = env->GetMethodID(JavaCallbackThreadClass, "callbackAudioGetBuffer", "()[S");
	JavaExit = env->GetMethodID(JavaCallbackThreadClass, "callbackExit", "()V");
	JavaAudioExit = env->GetMethodID(JavaCallbackThreadClass, "callbackAudioShutdown","()V");

	//locnet, 2011-04-28, support 2.1 or below
	JavaVideoGetBuffer = env->GetMethodID(JavaCallbackThreadClass, "callbackVideoGetBuffer", "()Ljava/nio/Buffer;");

	myLoader.bmph = bitmap;
	myLoader.width = width;
	myLoader.height = height;
	myLoader.rowbytes = myLoader.width*2;


	loadf=&myLoader;
	enableSound = myLoader.soundEnable;
	enableCycleHack = myLoader.cycleHack;
	enableRefreshHack = myLoader.refreshHack;
	enableMixerHack = myLoader.mixerHack;
	enableGlide = myLoader.glideEnable;
	//enableAutoCPU = myLoader.autoCPU;
}

void Android_ShutDown() {
	//locnet, 2011-04-28, support 2.1 or below
	JavaVideoGetBuffer = NULL;

	JavaAudioGetBuffer = NULL;
	JavaAudioWriteBuffer = NULL;
	JavaAudioInit = NULL;
	JavaVideoRedraw = NULL;
	JavaCallbackThreadClass = NULL;

	while (eventQueue.size())
		eventQueue.pop();

	atexit(Android_Exit);
	exit(0);
}

#define AKEYCODE_INVALID -1

//addition key not defined in keycodes.h
#define AKEYCODE_ESCAPE	111
#define AKEYCODE_FORWARD_DEL	112
#define AKEYCODE_CTRL_LEFT		113
#define AKEYCODE_SCROLL_LOCK 116
#define AKEYCODE_SYSRQ	120
#define AKEYCODE_PAUSE_BREAK 121
#define AKEYCODE_HOME	122
#define AKEYCODE_END	123
#define AKEYCODE_INSERT	124

//fishstix, additional keycodes to support ASUS transformer keybd
#define AKEYCODE_ALT_RIGHT		58
#define AKEYCODE_CTRL_RIGHT		114

#define AKEYCODE_F1	131
#define AKEYCODE_F2	132
#define AKEYCODE_F3	133
#define AKEYCODE_F4	134
#define AKEYCODE_F5	135
#define AKEYCODE_F6	136
#define AKEYCODE_F7	137
#define AKEYCODE_F8	138
#define AKEYCODE_F9	139
#define AKEYCODE_F10	140
#define AKEYCODE_F11	141
#define AKEYCODE_F12	142

//locnet, 2011-05-30, add more key support
#define AKEYCODE_NUM_LOCK	143
#define AKEYCODE_NUMPAD_0	144
#define AKEYCODE_NUMPAD_1	145
#define AKEYCODE_NUMPAD_2	146
#define AKEYCODE_NUMPAD_3	147
#define AKEYCODE_NUMPAD_4	148
#define AKEYCODE_NUMPAD_5	149
#define AKEYCODE_NUMPAD_6	150
#define AKEYCODE_NUMPAD_7	151
#define AKEYCODE_NUMPAD_8	152
#define AKEYCODE_NUMPAD_9	153
#define AKEYCODE_NUMPAD_DIVIDE	154
#define AKEYCODE_NUMPAD_MULTIPLY	155
#define AKEYCODE_NUMPAD_SUBTRACT	156
#define AKEYCODE_NUMPAD_ADD	157
#define AKEYCODE_NUMPAD_DOT	158
#define AKEYCODE_NUMPAD_ENTER	160

//fishstix - more keyboard support

void getKeyFromUnicode(int unicode, struct locnet_al_event *event);
void getKeyFromKeyCode(int keyCode, struct locnet_al_event *event);

extern "C"
JNIEXPORT jint JNICALL Java_com_fishstix_dosboxfree_DosBoxControl_nativeKey(JNIEnv * env, jobject obj, jint keyCode, jint down, jint ctrl, jint alt, jint shift)
{
	struct locnet_al_event	event;
	event.keycode = KBD_NONE;

    switch (keyCode) {
        case 100:
            event.keycode = KBD_z;
            break;
        case 101:
            event.keycode = KBD_space;
            break;
        case 102:
            event.keycode = KBD_slash;
    }

	if (event.keycode != KBD_NONE) {

		event.eventType = (down)?SDL_KEYDOWN:SDL_KEYUP;
		event.modifier = 0;

		eventQueue.push(event);

		return 1;
	}
	else {
		return 0;
	}
}

void tableEvent(int);

extern "C"
JNIEXPORT void JNICALL Java_com_fishstix_dosboxfree_DosBoxControl_nativeTableEvent(JNIEnv* env, jobject obj, jint eventId)
{
    tableEvent(eventId);
}

void tableEvent(int i) {
    struct locnet_al_event	event;
    switch (i)
    {
        // reload table
        case 0:
            event.keycode = KBD_enter;
            event.eventType = SDL_KEYDOWN;
            event.modifier = 0;

            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);

            event.keycode = KBD_f2;
            event.eventType = SDL_KEYDOWN;

            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);

            break;
        // toggle sound
        case 1:

            event.keycode = KBD_o;
            event.eventType = SDL_KEYDOWN;
            event.modifier = 0;
            event.modifier |= KEYBOARD_ALT_FLAG;

            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);

            event.keycode = KBD_m;
            event.eventType = SDL_KEYDOWN;
            event.modifier = 0;
            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);

            event.keycode = KBD_f3;
            event.eventType = SDL_KEYDOWN;
            event.modifier = 0;
            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);

            break;
        // exit game
        case 2:
            event.keycode = KBD_f4;
            event.eventType = SDL_KEYDOWN;
            event.modifier = 0;
            event.modifier |= KEYBOARD_ALT_FLAG;
            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);

            break;
        // save game score permanently
        case 3:
            // ALT + F4
            tableEvent(2);
            // ENTER, (F2)
            tableEvent(0);

            break;
        // show scores
        case 4:
            event.keycode = KBD_g;
            event.eventType = SDL_KEYDOWN;
            event.modifier = 0;
            event.modifier |= KEYBOARD_ALT_FLAG;

            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);

            event.keycode = KBD_h;
            event.eventType = SDL_KEYDOWN;
            event.modifier = 0;
            eventQueue.push(event);

            event.eventType = SDL_KEYUP;
            eventQueue.push(event);
    }
}
extern "C"
JNIEXPORT void JNICALL Java_com_fishstix_dosboxfree_DosBoxControl_nativeJoystick(JNIEnv * env, jobject obj, jint x, jint y, jint action, jint button)
{

}

extern "C"
JNIEXPORT void JNICALL Java_com_fishstix_dosboxfree_DosBoxControl_nativeMouse(JNIEnv * env, jobject obj, jint x, jint y, jint down_x, jint down_y, jint action, jint button)
{
/*	struct locnet_al_event	event;

	event.eventType = SDL_NOEVENT;

	switch (action) {
		case 0:
			event.eventType = SDL_MOUSEBUTTONDOWN;
			event.down_x = down_x;
			event.down_y = down_y;
			event.keycode = button;
			//LOGD(LOG_TAG, "mouseDown ->  action: %d  button: %d", action,button);
			break;
		case 1:
			event.eventType = SDL_MOUSEBUTTONUP;
			event.keycode = button;
			//LOGD(LOG_TAG, "mouseUp ->  action: %d  button: %d", action,button);
			break;
		case 2:
			event.eventType = SDL_MOUSEMOTION;
			event.down_x = down_x;
			event.down_y = down_y;
			event.x = x;
			event.y = y;
			break;
		case 3:
			event.eventType = SDL_MOUSEMOTION_WARP;
			event.x = x;
			event.y = y;
			break;
	}

	if 	(event.eventType != SDL_NOEVENT) {
		eventQueue.push(event);
		//LOGD(LOG_TAG, "push action: %d  button: %d", action,button);
	}*/
}

// fishstix
extern "C"
JNIEXPORT void JNICALL Java_com_fishstix_dosboxfree_DosBoxControl_nativeMouseWarp(JNIEnv * env, jobject obj, jfloat x, jfloat y, jint dst_left, jint dst_top, jint width, jint height) {
	/*struct locnet_al_event	event;
	float abs_x = (x - dst_left) / (float)(width);
	float abs_y = (y - dst_top) / (float)(height);
	//LOGD(LOG_TAG, "mouse warp x->%f y->%f wid->%f hei->%f dst_left->%f dst_top->%f",x,y,width,height,dst_left,dst_top);
	if (abs_x < 0) {
		abs_x = 0;
	}

	event.eventType = SDL_MOUSEMOTION_ABSOLUTE;
	event.down_x = abs_x;
	event.down_y = abs_y;
	eventQueue.push(event);
	//LOGD(LOG_TAG, "mouse warp x->%f y->%f",abs_x,abs_y);*/
}

/*
extern "C" void Java_com_fishstix_dosboxfree_DosBoxControl_nativeMouseWarp(JNIEnv * env, jobject obj, jint x, jint y, jfloat xfactor, jfloat yfactor, jint src_left, jint src_right, jint src_top, jint src_bottom, jint dst_left, jint dst_right, jint dst_top, jint dst_bottom) {
	struct locnet_al_event	event;
	struct locnet_al_event	event2;

//	if ( (x <= dst_right) && (x >= dst_left) && (y <= dst_bottom) && (y >= dst_top) ) {
	// Handle Absolute mouse movements
		float xval = (src_right*xfactor)/(dst_right-dst_left);
		float yval = (src_bottom*yfactor)/(dst_bottom-dst_top);
		x = x*xval-(dst_left*xval);
		y = y*yval-(dst_top*yval);
		event.eventType = SDL_MOUSEMOTION_WARP;
		event.x = x;
		event.y = y;

		eventQueue.push(event);

		event2.eventType = SDL_MOUSEMOTION;
		event2.down_x = x;
		event2.down_y = y;
		event2.x = x;
		event2.y = y;

		eventQueue.push(event2);
//	}
}
*/

void Android_AudioGetBuffer() {
	if ((loadf != 0) && (loadf->abort == 0) && (gEnv != 0))
		loadf->audioBuffer = (jshortArray)gEnv->CallObjectMethod( JavaCallbackThread, JavaAudioGetBuffer );
}

extern bool CPU_CycleAutoAdjust;
extern bool CPU_SkipCycleAutoAdjust;

void Android_AudioWriteBuffer()
{
	short size = 0;

	if ((loadf != 0) && (loadf->abort == 0) && (gEnv != 0)) {

		if ((mixerCallBack != 0) && (loadf->audioBuffer != 0)) {
			jboolean isCopy = JNI_TRUE;
			jsize len = gEnv->GetArrayLength(loadf->audioBuffer)*((CPU_CycleAutoAdjust||CPU_SkipCycleAutoAdjust)?0.8:1);
			jshort *audioBuffer = gEnv->GetShortArrayElements(loadf->audioBuffer, &isCopy);

			size = 0;

			(*mixerCallBack)(&size, (unsigned char *)audioBuffer, (len << 1));

			gEnv->ReleaseShortArrayElements(loadf->audioBuffer, audioBuffer, 0);

			if (size > 0) {
				if (enableMixerHack)
					gEnv->CallVoidMethod( JavaCallbackThread, JavaAudioWriteBuffer, (int)size>>1);
				else
					gEnv->CallVoidMethod( JavaCallbackThread, JavaAudioWriteBuffer, (int)size);
			}
		}
	}
}

int Android_OpenAudio(int rate, int channels, int encoding, int bufSize)
{
	if ((loadf != 0) && (loadf->abort == 0) && (gEnv != 0))
		return gEnv->CallIntMethod( JavaCallbackThread, JavaAudioInit, rate, channels, encoding, bufSize );
	else
		return 0;
}

void Android_CloseAudio() {
	gEnv->CallVoidMethod(JavaCallbackThread, JavaAudioExit);
}

int Android_PollEvent(struct locnet_al_event *event)
{
	if (eventQueue.size() > 0) {
		if (event) {
			*event = eventQueue.front();
			eventQueue.pop();
		}
		return 1;
	}
	return 0;
}

void Android_Exit() {
	if (gEnv != 0) {
		JNIEnv *env = gEnv;

		gEnv = NULL;

		env->CallVoidMethod( JavaCallbackThread, JavaExit);

		env->DeleteGlobalRef(JavaCallbackThread);
		JavaCallbackThread = NULL;
	}
}

void Android_SetVideoMode(int width, int height, int depth) {
	if ((loadf != 0) && (gEnv != 0)) {
		if ((width != loadf->width) || (height != loadf->height)) {
			jobject bmph = gEnv->CallObjectMethod( JavaCallbackThread, JavaVideoSetMode, width, height );

			if (bmph) {
				loadf->bmph = bmph;
				loadf->width = width;
				loadf->height = height;
				loadf->rowbytes = width*2;

#if !USE_JNIGRAPHIC
				//locnet, 2011-04-28, support 2.1 or below
				loadf->videoBuffer = Android_VideoGetBuffer();
#endif
			}
		}
	}
}

char *Android_VideoGetBuffer() {
	char * result = 0;

	jobject videoBuffer = gEnv->CallObjectMethod( JavaCallbackThread, JavaVideoGetBuffer );
	if (videoBuffer != 0) {
		result = (char *)gEnv->GetDirectBufferAddress(videoBuffer);
		gEnv->DeleteLocalRef(videoBuffer);
		videoBuffer = 0;
	}

	return result;
}

void	Android_LockSurface() {
	if ((gEnv != 0) && (loadf != 0) && (loadf->bmph != 0)) {
#if USE_JNIGRAPHIC
		void* pixels = 0;

		AndroidBitmap_lockPixels(gEnv, loadf->bmph, &pixels);
		loadf->videoBuffer = (char *)pixels;
#else
		//locnet, 2011-04-28, support 2.1 or below
		if (loadf->videoBuffer == 0)
			loadf->videoBuffer = Android_VideoGetBuffer();
#endif
	}
}

void	Android_UnlockSurface(int startLine, int endLine)
{
	if ((gEnv != 0) && (loadf != 0) && (loadf->bmph != 0) && (loadf->videoBuffer != 0)) {
#if USE_JNIGRAPHIC
		AndroidBitmap_unlockPixels(gEnv, loadf->bmph);
		loadf->videoBuffer = 0;
#endif
	}

	if ((loadf != 0) && (loadf->abort == 0) && (gEnv != 0) && (endLine > startLine))
		gEnv->CallVoidMethod( JavaCallbackThread, JavaVideoRedraw, loadf->width, loadf->height, startLine, endLine );
}

void 	Android_ResetScreen()
{
	if ((gEnv != 0) && (loadf != 0) && (loadf->bmph != 0)) {
		void* pixels = 0;

#if USE_JNIGRAPHIC
		AndroidBitmap_lockPixels(gEnv, loadf->bmph, &pixels);
#else
		//locnet, 2011-04-28, support 2.1 or below
		pixels = Android_VideoGetBuffer();
#endif

		if (pixels != 0)
			memset(pixels, 0, loadf->width*loadf->height*2);

#if USE_JNIGRAPHIC
		AndroidBitmap_unlockPixels(gEnv, loadf->bmph);
#endif
	}
}


void getKeyFromUnicode(int unicode, struct locnet_al_event *event)
{

	switch (unicode) {
		case '!': case '@':	case '#': case '$': case '%': case '^': case '&': case '*':	case '(': case ')':
		case '~': case '_': case '+': case '?': case '{': case '}': case ':': case '"': case '<': case '>':
		case '|':
			event->modifier = KEYBOARD_SHIFT_FLAG;
			break;
		default:
			if ((unicode >= 'A') && (unicode <= 'Z')) {
				event->modifier = KEYBOARD_SHIFT_FLAG;
			}
			break;
	}
	int dosboxKeycode = KBD_NONE;
	switch (unicode){
		case '!': case '1': dosboxKeycode = KBD_1; break;
		case '@': case '2': dosboxKeycode = KBD_2; break;
		case '#': case '3': dosboxKeycode = KBD_3; break;
		case '$': case '4': dosboxKeycode = KBD_4; break;
		case '%': case '5': dosboxKeycode = KBD_5; break;
		case '^': case '6': dosboxKeycode = KBD_6; break;
		case '&': case '7': dosboxKeycode = KBD_7; break;
		case '*': case '8': dosboxKeycode = KBD_8; break;
		case '(': case '9': dosboxKeycode = KBD_9; break;
		case ')': case '0': dosboxKeycode = KBD_0; break;
		case 'a': case 'A':dosboxKeycode = KBD_a; break;
		case 'b': case 'B': dosboxKeycode = KBD_b; break;
		case 'c': case 'C': dosboxKeycode = KBD_c; break;
		case 'd': case 'D': dosboxKeycode = KBD_d; break;
		case 'e': case 'E': dosboxKeycode = KBD_e; break;
		case 'f': case 'F': dosboxKeycode = KBD_f; break;
		case 'g': case 'G': dosboxKeycode = KBD_g; break;
		case 'h': case 'H': dosboxKeycode = KBD_h; break;
		case 'i': case 'I': dosboxKeycode = KBD_i; break;
		case 'j': case 'J': dosboxKeycode = KBD_j; break;
		case 'k': case 'K': dosboxKeycode = KBD_k; break;
		case 'l': case 'L': dosboxKeycode = KBD_l; break;
		case 'm': case 'M': dosboxKeycode = KBD_m; break;
		case 'n': case 'N': dosboxKeycode = KBD_n; break;
		case 'o': case 'O': dosboxKeycode = KBD_o; break;
		case 'p': case 'P': dosboxKeycode = KBD_p; break;
		case 'q': case 'Q': dosboxKeycode = KBD_q; break;
		case 'r': case 'R': dosboxKeycode = KBD_r; break;
		case 's': case 'S': dosboxKeycode = KBD_s; break;
		case 't': case 'T': dosboxKeycode = KBD_t; break;
		case 'u': case 'U': dosboxKeycode = KBD_u; break;
		case 'v': case 'V': dosboxKeycode = KBD_v; break;
		case 'w': case 'W': dosboxKeycode = KBD_w; break;
		case 'x': case 'X': dosboxKeycode = KBD_x; break;
		case 'y': case 'Y': dosboxKeycode = KBD_y; break;
		case 'z': case 'Z': dosboxKeycode = KBD_z; break;
		case 0x08: dosboxKeycode = KBD_backspace; break;
		case 0x09: dosboxKeycode = KBD_tab; break;
		case 0x20: dosboxKeycode = KBD_space; break;
		case 0x0A: dosboxKeycode = KBD_enter; break;
		case '~': case '`': dosboxKeycode = KBD_grave; break;
		case '_': case '-': dosboxKeycode = KBD_minus; break;
		case '+': case '=': dosboxKeycode = KBD_equals; break;
		case '?': case '/': dosboxKeycode = KBD_slash; break;
		case '{': case '[': dosboxKeycode = KBD_leftbracket; break;
		case '}': case ']': dosboxKeycode = KBD_rightbracket; break;
		case ':': case ';': dosboxKeycode = KBD_semicolon; break;
		case '"': case '\'': dosboxKeycode = KBD_quote; break;
		case '<': case ',': dosboxKeycode = KBD_comma; break;
		case '>': case '.': dosboxKeycode = KBD_period; break;
		case '|': case '\\': dosboxKeycode = KBD_backslash; break;
		case 0x1B: dosboxKeycode = KBD_esc; break;
		case 0x1C: dosboxKeycode = KBD_left; break;
		case 0x1D: dosboxKeycode = KBD_right; break;
		case 0x1E: dosboxKeycode = KBD_up; break;
		case 0x1F: dosboxKeycode = KBD_down; break;
		default: dosboxKeycode = KBD_NONE; break;
	}
	event->keycode = dosboxKeycode;
}
