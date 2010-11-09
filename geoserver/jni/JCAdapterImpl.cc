/* The JCAdapter.c file, which implements the native function */

#include <jni.h>      /* Java Native Interface headers */
#include <stdlib.h> 
#include "JCAdapter.h"   /* Auto-generated header created by javah -jni */

#include <math.h>     /* Include math.h for the prototype of function y0 */

#include "../../lib/source/core/configuration.h"
#include "../../lib/source/core/size.h"
#include "../../lib/source/acid_maps.h"

/* Our C definition of the function bessely0 declared in Bessel.java */

int getIntField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "I");
	int value = env->GetIntField(jconfiguration, fieldId);
	return value;
}

float getFloatField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "F");
	float value = env->GetFloatField(jconfiguration, fieldId);
	return value;
}

float* getFloatArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[F");
	jfloatArray value = (jfloatArray)env->GetObjectField(jconfiguration, fieldId);
	if(value){
		return env->GetFloatArrayElements(value, NULL);
	} else {
		return NULL;
	}
}

int* getIntArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[I");
	jintArray value = (jintArray)env->GetObjectField(jconfiguration, fieldId);
	if(value){
		return env->GetIntArrayElements(value, NULL);
	} else {
		return NULL;
	}
}

acid_maps::Bounds* getBoundField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jclass boundClass = env->FindClass("com/xoomcode/acidmaps/core/Bounds");

	jfieldID fieldId = env->GetFieldID(configurationClass, id, "Lcom/xoomcode/acidmaps/core/Bounds;");
	jobject jbounds = (jobject)env->GetObjectField(jconfiguration, fieldId);

	if(jbounds){
		acid_maps::Bounds* bound= new acid_maps::Bounds();
		bound->min_x = getFloatField(env, boundClass, jbounds, "minY");
		bound->max_y = getFloatField(env, boundClass, jbounds, "maxY");
		bound->min_y = getFloatField(env, boundClass, jbounds, "minY");
		bound->max_x = getFloatField(env, boundClass, jbounds, "maxX");
		return bound;
	} else {
		return NULL;
	}
}

acid_maps::Configuration* buildConfiguration(JNIEnv* env, jobject jconfiguration){
	acid_maps::Configuration* configuration = new acid_maps::Configuration();

	jclass configurationClass = env->FindClass("com/xoomcode/acidmaps/core/Configuration");

	configuration->bounds = getBoundField(env, configurationClass, jconfiguration, "bounds");
 	configuration->dataset = getFloatArrayField(env, configurationClass, jconfiguration, "dataset");
	configuration->simplify_method = getIntField(env, configurationClass, jconfiguration, "simplifyMethod");
 	configuration->dataset_size = getIntField(env, configurationClass, jconfiguration, "datasetSize");
 	configuration->interpolation_strategy = getIntField(env, configurationClass, jconfiguration, "interpolationStrategy");

 	int width = getIntField(env, configurationClass, jconfiguration, "width");
 	int height = getIntField(env, configurationClass, jconfiguration, "height");
 	acid_maps::Size* tile_size = new acid_maps::Size(width, height);
 	configuration->tile_size = tile_size;

 	configuration->intervals = getIntArrayField(env, configurationClass, jconfiguration, "intervals");
 	configuration->interval_colors = getIntArrayField(env, configurationClass, jconfiguration, "intervalColors");
 	configuration->intervals_size = getIntField(env, configurationClass, jconfiguration, "intervalSize");
	return configuration;
}

JNIEXPORT void JNICALL Java_com_xoomcode_acidmaps_adapter_JCAdapter_interpolateC
  (JNIEnv* env, jobject obj, jobject jconfiguration, jbyteArray out)
{
 	jbyte* joutpt;
 	jboolean isCopy;

 	joutpt = env->GetByteArrayElements(out, &isCopy);
	acid_maps::Configuration* configuration = buildConfiguration(env, jconfiguration);

 	int outSize = configuration->tile_size->width * configuration->tile_size->height * 4;
	unsigned char* charOut = new unsigned char[outSize];
	//acid_maps::generate(configuration, charOut);
		// TODO return output_buffer to java
		//delete[] configuration->output_buffer;
		//delete configuration;

 	/*joutpt = new jbyte[outSize];

 	for (int i = 0; i < outSize; ++i) {
 		joutpt[i] = charOut[i];
	}*/
	
	env->ReleaseByteArrayElements(out, joutpt, 0);
 	//delete charOut;

}


