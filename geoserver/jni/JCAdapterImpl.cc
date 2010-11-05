/* The JCAdapter.c file, which implements the native function */

#include <jni.h>      /* Java Native Interface headers */
#include <stdlib.h> 
#include "JCAdapter.h"   /* Auto-generated header created by javah -jni */

#include <math.h>     /* Include math.h for the prototype of function y0 */

#include "../../lib/source/core/configuration.h"
#include "../../lib/source/acid_maps.h"

/* Our C definition of the function bessely0 declared in Bessel.java */

int getIntField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "I");
	int value = env->GetIntField(jconfiguration, fieldId);
	return value;
}

float getFloatField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "F");
	float value = env->GetFloatField(jconfiguration, fieldId);
	return value;
}

float* getFloatArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[F");
	jfloatArray value = (jfloatArray)env->GetObjectField(jconfiguration, fieldId);
	if(value){
		return env->GetFloatArrayElements(value, NULL);
	} else {
		return NULL;
	}
}

acid_maps::Bounds* getBoundField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, char* id) {
	jclass boundClass = env->FindClass("com/xoomcode/acidmaps/core/Bounds");

	jfieldID fieldId = env->GetFieldID(configurationClass, id, "Lcom/xoomcode/acidmaps/core/Bounds;");
	jobject jbounds = (jobject)env->GetObjectField(jconfiguration, fieldId);

	if(jbounds){
		acid_maps::Bounds* bound= new acid_maps::Bounds();
		bound->bottom = getFloatField(env, boundClass, jbounds, "bottom");
		bound->left = getFloatField(env, boundClass, jbounds, "left");
		bound->right = getFloatField(env, boundClass, jbounds, "right");
		bound->top = getFloatField(env, boundClass, jbounds, "top");
		return bound;
	} else {
		return NULL;
	}
}

acid_maps::Configuration* buildConfiguration(JNIEnv* env, jobject jconfiguration){
	acid_maps::Configuration* configuration = new acid_maps::Configuration();

	jclass configurationClass = env->FindClass("com/xoomcode/acidmaps/core/Configuration");

	configuration->tile_bounds = getBoundField(env, configurationClass, jconfiguration, "tileBounds");
	configuration->map_bounds = getBoundField(env, configurationClass, jconfiguration, "mapBounds");
 	configuration->dataset = getFloatArrayField(env, configurationClass, jconfiguration, "dataset");
	configuration->simplify_method = getIntField(env, configurationClass, jconfiguration, "simplifyMethod");
 	configuration->dataset_size = getIntField(env, configurationClass, jconfiguration, "datasetSize");
 	configuration->interpolation_strategy = getIntField(env, configurationClass, jconfiguration, "interpolationStrategy");
 	configuration->width = getIntField(env, configurationClass, jconfiguration, "width");
 	configuration->height = getIntField(env, configurationClass, jconfiguration, "height");
 	configuration->color_depth = getIntField(env, configurationClass, jconfiguration, "colorDepth");

	return configuration;
}

JNIEXPORT void JNICALL Java_com_xoomcode_acidmaps_adapter_JCAdapter_interpolateC
  (JNIEnv* env, jobject obj, jobject jconfiguration, jbyteArray out)
{
 	jbyte* joutpt;
 	jboolean isCopy;

 	

 	joutpt = env->GetByteArrayElements(out, &isCopy);
	acid_maps::Configuration* configuration = buildConfiguration(env, jconfiguration);

 	int outSize = configuration->width * configuration->height * configuration->color_depth;
	char* charOut = new char[outSize];
	acid_maps::generate(configuration, charOut);
	// TODO return output_buffer to java
	//delete[] configuration->output_buffer;
	//delete configuration;

 	joutpt = new jbyte[outSize];

 	for (int i = 0; i < outSize; ++i) {
 		joutpt[i] = charOut[i];
	}
	
	env->ReleaseByteArrayElements(out, joutpt, 0);
 	//delete charOut;

}


