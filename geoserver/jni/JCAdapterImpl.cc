/* The JCAdapter.c file, which implements the native function */

#include <jni.h>      /* Java Native Interface headers */
#include <string.h>      /* Java Native Interface headers */
#include <stdlib.h> 
#include "JCAdapter.h"   /* Auto-generated header created by javah -jni */

#include <math.h>     /* Include math.h for the prototype of function y0 */

#include "../../lib/source/core/configuration.h"
#include "../../lib/source/core/size.h"
#include "../../lib/source/acid_maps.h"
#include "../../lib/source/render/renderer_type.h"
#include "../../lib/source/constants/constants.h"

/* Our C definition of the function bessely0 declared in Bessel.java */
namespace ams = acid_maps;

int getFloatArrayLength(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[F");
	jarray value = (jarray)env->GetObjectField(jconfiguration, fieldId);
	if(value){
		int length = env->GetArrayLength(value);
		//printf("%s size: %d\n", id, length);
		return length;
	} else {
		return 0;
	}
}

int getCharArrayLength(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[B");
	jarray value = (jarray)env->GetObjectField(jconfiguration, fieldId);
	if(value){
		int length = env->GetArrayLength(value);
		//printf("%s size: %d\n", id, length);
		return length;
	} else {
		return 0;
	}
}

int getIntArrayLength(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[I");
	jarray value = (jarray)env->GetObjectField(jconfiguration, fieldId);
	if(value){
		int length = env->GetArrayLength(value);
		//printf("%s size: %d\n", id, length);
		return length;
	} else {
		return 0;
	}
}

int getIntField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "I");
	int value = env->GetIntField(jconfiguration, fieldId);
	//printf("%s: %d\n", id, value);
	return value;
}

float getFloatField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "F");
	float value = env->GetFloatField(jconfiguration, fieldId);
	//printf("%s: %f\n", id, value);
	return value;
}

float* getFloatArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[F");
	jfloatArray value = (jfloatArray)env->GetObjectField(jconfiguration, fieldId);
	int size = getFloatArrayLength(env, configurationClass, jconfiguration, id);

	if(value){
		float* floatArray = env->GetFloatArrayElements(value, NULL);
		/*printf("%s: [ ", id);
		for (int i = 0; i < size; ++i) {
			printf("%f, ", floatArray[i]);
		}
		printf(" ]\n");*/
		return floatArray;
	} else {
		return NULL;
	}
}

int* getIntArrayField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jfieldID fieldId = env->GetFieldID(configurationClass, id, "[I");
	jintArray value = (jintArray)env->GetObjectField(jconfiguration, fieldId);
	int size = getIntArrayLength(env, configurationClass, jconfiguration, id);
	if(value){
		int* intArray = env->GetIntArrayElements(value, NULL);
		/*printf("%s: [ ", id);
		for (int i = 0; i < size; ++i) {
			printf("%d, ", intArray[i]);
		}
		printf(" ]\n");*/
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
		/*printf("%s: [ ", id);
		for (int i = 0; i < size; ++i) {
			printf("%c, ", charArray[i]);
		}
		printf(" ]\n");*/
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
//
//		/*printf("%s: [ ", id);
//		for (int i = 0; i < size; ++i) {
//			printf("%c, ", charArray[i]);
//		}
//		printf(" ]\n");*/
		return pointArray;
    } else {
		return NULL;
	}
}

ams::Bounds* getBoundField(JNIEnv* env, jclass configurationClass, jobject jconfiguration, const char* id) {
	jclass boundClass = env->FindClass("com/xoomcode/acidmaps/core/Bounds");

	jfieldID fieldId = env->GetFieldID(configurationClass, id, "Lcom/xoomcode/acidmaps/core/Bounds;");
	jobject jbounds = (jobject)env->GetObjectField(jconfiguration, fieldId);

	if(jbounds){
		ams::Bounds* bound= new ams::Bounds();
		bound->min_x = getFloatField(env, boundClass, jbounds, "minX");
		bound->min_y = getFloatField(env, boundClass, jbounds, "minY");
		bound->max_x = getFloatField(env, boundClass, jbounds, "maxX");
		bound->max_y = getFloatField(env, boundClass, jbounds, "maxY");
		return bound;
	} else {
		return NULL;
	}
}

ams::Configuration* buildConfiguration(JNIEnv* env, jobject jconfiguration){
	ams::Configuration* configuration = new ams::Configuration();

	jclass configurationClass = env->FindClass("com/xoomcode/acidmaps/core/Configuration");

	configuration->bounds = getBoundField(env, configurationClass, jconfiguration, "bounds");
 	configuration->dataset_size = getIntField(env, configurationClass, jconfiguration, "datasetSize");
 	configuration->dataset = getPointArrayField(env, configurationClass, jconfiguration, "dataset", configuration->dataset_size);

 	// FIXME: get Point array

	configuration->simplify_method = getIntField(env, configurationClass, jconfiguration, "simplifyMethod");
	configuration->simplify_size = getIntField(env, configurationClass, jconfiguration, "simplifySize");
 	configuration->interpolation_strategy = getIntField(env, configurationClass, jconfiguration, "interpolationStrategy");

 	int width = getIntField(env, configurationClass, jconfiguration, "width");
 	int height = getIntField(env, configurationClass, jconfiguration, "height");
 	ams::Size* tile_size = new ams::Size(width, height);
 	configuration->tile_size = tile_size;

 	configuration->intervals = getFloatArrayField(env, configurationClass, jconfiguration, "intervals");
 	configuration->intervals_colors = getCharArrayField(env, configurationClass, jconfiguration, "intervalsColors");
 	configuration->intervals_size = getCharArrayLength(env, configurationClass, jconfiguration, "intervalsColors") / ams::RGBA;
 	configuration->renderer_type = getIntField(env, configurationClass, jconfiguration, "rendererType");
 	configuration->interpolation_parameter = getIntField(env, configurationClass, jconfiguration, "interpolationParameter");
 	configuration->format = getIntField(env, configurationClass, jconfiguration, "format");

	return configuration;
}

JNIEXPORT jobject JNICALL Java_com_xoomcode_acidmaps_adapter_JCAdapter_interpolateC
  (JNIEnv* env, jobject obj, jobject jconfiguration)
{
	ams::Configuration* configuration = buildConfiguration(env, jconfiguration);

	unsigned char* charOut;
	unsigned int charOutSize;
	ams::generate(configuration, &charOut, &charOutSize);
 	jbyte* joutpt = new jbyte[charOutSize];

 	memcpy(joutpt, charOut, charOutSize * sizeof(unsigned char));

 	jbyteArray out = env->NewByteArray(charOutSize);
	env->SetByteArrayRegion(out, 0, charOutSize, joutpt);

	delete[] configuration->dataset;
	delete configuration->bounds;
	delete configuration->tile_size;
	delete[] configuration->intervals;
	delete[] configuration->intervals_colors;
	delete configuration;
	delete[] joutpt;
	free(charOut);

	return out;
}


