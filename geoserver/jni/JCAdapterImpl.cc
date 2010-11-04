/* The JCAdapter.c file, which implements the native function */

#include <jni.h>      /* Java Native Interface headers */
#include <stdlib.h> 
#include "JCAdapter.h"   /* Auto-generated header created by javah -jni */

#include <math.h>     /* Include math.h for the prototype of function y0 */

#include "../../lib/source/core/configuration.h"

/* Our C definition of the function bessely0 declared in Bessel.java */

void interpolate(char* out, int* size){
	*size = 5;
	//out = (char*)malloc(sizeof(char)*(*size));
	out[0] = 'l';
	out[1] = 'a';
	out[2] = 'n';
	out[3] = 'a';
	//free(out);
}

JNIEXPORT void JNICALL Java_com_xoomcode_acidmaps_adapter_JCAdapter_interpolateC
  (JNIEnv *env, jobject obj, jobject configuration, jbyteArray out)
{
 	jbyte *outpt;
 	jboolean isCopy;
 	
	jclass cls = env->FindClass("com/xoomcode/acidmaps/Configuration");
 	jfieldID ageId = env->GetFieldID(cls, "age", "I");
 	int intFieldVal = env->GetIntField(configuration, ageId);

 	outpt = env->GetByteArrayElements(out, &isCopy);
 		
 	outpt[0] = 'c';
 	outpt[1] = 'a';
 	outpt[2] = 's';
 	outpt[3] = 'a';
	//outpt[4] = intFieldVal;
	
	env->ReleaseByteArrayElements(out, outpt, 0);
	
}

