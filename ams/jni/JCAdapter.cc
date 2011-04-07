/* The JCAdapter.c file, which implements the native function */

#include "JCAdapter.h" /* Auto-generated header created by javah -jni */

#include <jni.h>       /* Java Native Interface headers */
#include <string.h>    /* Java Native Interface headers */
#include <stdlib.h> 
#include <math.h>      /* Include math.h for the prototype of function y0 */

#include "../src/core/configuration.h"
#include "../src/core/size.h"
#include "../src/core/color.h"
#include "../src/acid_maps.h"
#include "../src/render/renderer_type.h"
#include "../src/constants/constants.h"

namespace ams = acid_maps;

int getArrayLength(JNIEnv* env, jclass configurationClass, jobject jconfiguration, jfieldID fieldId) {
	jarray field = (jarray)env->GetObjectField(jconfiguration, fieldId);
	int length = 0;
	if(field) length = env->GetArrayLength(value);
	return length;
}

int getFloatArrayLength(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[F");
	return getArrayLength(env, configurationClass, jconfiguration, fieldId);
}

int getCharArrayLength(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[B");
	return getArrayLength(env, configurationClass, jconfiguration, fieldId);
}

int getIntArrayLength(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[I");
	return getArrayLength(env, configurationClass, jconfiguration, fieldId);
}

int getIntField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "I");
	return env->GetIntField(jconfiguration, fieldId);
}

char getByteField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "B");
	return env->GetByteField(jconfiguration, fieldId);
}

float getFloatField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "F");
	return env->GetFloatField(jconfiguration, fieldId);
}

float* getFloatArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[F");
	jfloatArray value = (jfloatArray)env->GetObjectField(jconfiguration, fieldId);
	int size = getFloatArrayLength(env, configurationClass, jconfiguration, id);

	if(value){
		float* floatArray = env->GetFloatArrayElements(value, NULL);
		return floatArray;
	} else {
		return NULL;
	}
}

jint* getIntArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[I");
	jintArray value = (jintArray)env->GetObjectField(jconfiguration, fieldId);
	int size = getIntArrayLength(env, configurationClass, jconfiguration, id);
	if(value){
		jint* intArray = env->GetIntArrayElements(value, NULL);
		return intArray;
	} else {
		return NULL;
	}
}

unsigned char* getCharArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[B");
	jbyteArray value = (jbyteArray)env->GetObjectField(jconfiguration, fieldId);
	int size = getCharArrayLength(env, configurationClass, jconfiguration, id);
	if(value){
		unsigned char* charArray = (unsigned char*)env->GetByteArrayElements(value, NULL);
		return charArray;
	} else {
		return NULL;
	}
}

ams::Point* getPointArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id, int size) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[Lcom/xoomcode/acidmaps/core/Point;");
	jobjectArray value = (jobjectArray)env->GetObjectField(jconfiguration, fieldId);
	jclass pointClass = env->FindClass("com/xoomcode/acidmaps/core/Point");
	if(value){
		ams::Point* pointArray = new ams::Point[size];

		ams::Point* point= new ams::Point();
		for (int i = 0; i < size; ++i) {
			jobject jpoint = (jobject)env->GetObjectArrayElement(value, i);
			point->x = getFloatField(env, pointClass, jpoint, "x");
			point->y = getFloatField(env, pointClass, jpoint, "y");
			point->value = getFloatField(env, pointClass, jpoint, "value");
			memcpy(pointArray + i, point, sizeof(ams::Point));
		}
		delete point;
		return pointArray;
    } else {
		return NULL;
	}
}

ams::Color* getColorArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id, int size) {
  int position = 0;
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[Lcom/xoomcode/acidmaps/core/Color;");
	jobjectArray value = (jobjectArray)env->GetObjectField(jconfiguration, fieldId);
	jclass colorClass = env->FindClass("com/xoomcode/acidmaps/core/Color");
	
	ams::Color* colorArray = NULL;
	
	if(value){
    colorArray = new ams::Color[size];
  
	  ams::Color* color;
		for (int i = 0; i < size; i++) {
			jobject jcolor = (jobject)env->GetObjectArrayElement(value, i);
		  color = colorArray + i;
			color->r = getByteField(env, colorClass, jcolor, "r");
			color->g = getByteField(env, colorClass, jcolor, "g");
			color->b = getByteField(env, colorClass, jcolor, "b");
			color->a = getByteField(env, colorClass, jcolor, "a");
		}
  }
  
	return colorArray;
}

ams::Bounds* getBoundField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	ams::Bounds* bound = NULL;
	jclass boundClass = env->FindClass("com/xoomcode/acidmaps/core/Bounds");
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "Lcom/xoomcode/acidmaps/core/Bounds;");
	jobject jbounds = (jobject)env->GetObjectField(jconfiguration, fieldId);
	if(jbounds){
		bound = new ams::Bounds();
		bound->min_x = getFloatField(env, boundClass, jbounds, "minX");
		bound->min_y = getFloatField(env, boundClass, jbounds, "minY");
		bound->max_x = getFloatField(env, boundClass, jbounds, "maxX");
		bound->max_y = getFloatField(env, boundClass, jbounds, "maxY");
	}
	return bound;
}

void buildConfiguration(JNIEnv* env, jobject jconfiguration, ams::Configuration* configuration){
	jclass configurationClass = env->FindClass("com/xoomcode/acidmaps/core/Configuration");

	configuration->bounds = getBoundField(env, configurationClass, jconfiguration, "bounds");
 	configuration->dataset_size = getIntField(env, configurationClass, jconfiguration, "datasetSize");
 	configuration->dataset = getPointArrayField(env, configurationClass, jconfiguration, "dataset", configuration->dataset_size);

	configuration->simplify_method = getIntField(env, configurationClass, jconfiguration, "simplifyMethod");
	configuration->simplify_size = getIntField(env, configurationClass, jconfiguration, "simplifySize");
 	configuration->interpolation_strategy = getIntField(env, configurationClass, jconfiguration, "interpolationStrategy");

 	int width = getIntField(env, configurationClass, jconfiguration, "width");
 	int height = getIntField(env, configurationClass, jconfiguration, "height");
 	ams::Size* tile_size = new ams::Size(width, height);
 	configuration->tile_size = tile_size;

 	configuration->intervals = getFloatArrayField(env, configurationClass, jconfiguration, "intervals");
 	configuration->intervals_size = getFloatArrayLength(env, configurationClass, jconfiguration, "intervals");
 	configuration->intervals_colors = getColorArrayField(env, configurationClass, jconfiguration, "intervalsColors", configuration->intervals_size);
 	
 	configuration->renderer_type = getIntField(env, configurationClass, jconfiguration, "rendererType");
 	configuration->radius = getIntField(env, configurationClass, jconfiguration, "radius");
 	configuration->format = getIntField(env, configurationClass, jconfiguration, "format");
}

JNIEXPORT jobject JNICALL Java_com_xoomcode_acidmaps_adapter_JCAdapter_interpolateC
  (JNIEnv* env, jobject obj, jobject jconfiguration)
{
	ams::Configuration* configuration = new ams::Configuration();
	buildConfiguration(env, jconfiguration, configuration);

	unsigned char* charOut;
	unsigned int charOutSize;

	int error = ams::generate(configuration, &charOut, &charOutSize);
	
	jbyteArray out = NULL;
 	
 	if(error != 0){
 		jclass configurationClass = env->FindClass("com/xoomcode/acidmaps/core/Configuration");
 		jfieldID fieldId = env->GetFieldID(configurationClass, "error", "I");
 		env->SetIntField(jconfiguration, fieldId, error);
 	} else {
   	jbyte* joutpt = new jbyte[charOutSize];
   	memcpy(joutpt, charOut, charOutSize * sizeof(unsigned char));
   	out = env->NewByteArray(charOutSize);
   	env->SetByteArrayRegion(out, 0, charOutSize, joutpt);
 		free(charOut);
 		delete[] joutpt;
  }
  
	delete[] configuration->dataset;
	delete configuration->bounds;
	delete configuration->tile_size;
	delete[] configuration->intervals_colors;
	delete configuration;

	return out;
}


