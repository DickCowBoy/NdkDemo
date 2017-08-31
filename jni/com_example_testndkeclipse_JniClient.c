#include "com_example_testndkeclipse_JniClient.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
// ����logͷ�ļ�
#include  <android/log.h>
// log��ǩ
#define  TAG    "=====CSY====="
// ����info��Ϣ
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// ����debug��Ϣ
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// ����error��Ϣ
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#ifdef __cplusplus
extern "C"
{
#endif
/*
 * Class:     com_example_testndkeclipse_JniClient
 * Method:    AddStr
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 *
 * ʵ���ַ�����ƴ��
 */
JNIEXPORT jstring JNICALL Java_com_example_testndkeclipse_JniClient_AddStr(
		JNIEnv *env, jclass arg, jstring instringA, jstring instringB) {
	//jstring str = (*env)->NewStringUTF(env, instringA+"=="+instringB+"are from JNI");
	jstring str = (*env)->NewStringUTF(env, "I am from JNI");
	//LOGI("%d",len1);//c�������  ������eclipse�д�ӡ����  �÷���printf()

	//��jstringת����const char*ָ�룬ʹ��const���η���ʾ�����ݲ��ɱ��޸�
	const char* str1 = (*env)->GetStringUTFChars(env, instringA, NULL); //C���﷨
	//1.����java.lang.String��Ӧ��JNI����jstringʱ��û������ʻ�����������һ��ֱ��ʹ�ã�
	//��Ϊ����Java��һ���������ͣ������ڱ��ش�����ֻ��ͨ��GetStringUTFChars������JNI�����������ַ���������
	const char* str2 = (*env)->GetStringUTFChars(env, instringB, NULL);
	//2.const char* str1 = env->GetStringUTFChars(instringA,NULL);//C++���﷨

	//3.���һ���������Ƿ񿽱��ı�־
	//���B��ԭʼ�ַ���java.lang.String �Ŀ�������isCopy����ֵΪ JNI_TRUE��
	//���B��ԭʼ�ַ���ָ�����JVM�е�ͬһ�����ݣ��� isCopy����ֵΪ JNI_FALSE
	//��Ϊ�㲻�ع��� JVM �Ƿ�᷵��ԭʼ�ַ����Ŀ�������ֻ��ҪΪ isCopy����NULL��Ϊ����

//4.C�����У�Ϊʲô�ַ������Ը�ֵ���ַ�ָ�����
//
//	char *p,a='5';
//	p=&a;                     //��Ȼ����ȷ�ģ�
//	p="abcd";              //��ΪʲôҲ����������ֵ����
//
//	�ʣ�һֱ��ⲻ��Ϊʲô���Խ��ִ�������ֵ���ַ�ָ����������λָ�㣡
//
//	��
//	˫��������3���£�
//	1.�����˿ռ�(�ڳ�����)��������ַ���
//	2. ���ַ���β������'/0'
//	3.���ص�ַ

	//�������ַ�������
	int size = strlen(str1) + strlen(str2);

	//char *charPoint = new char[size+1];//C++�оͽ���ʹ��new��delete Ϊ�˼���,������malloc
	//char *str_point = new char[size+1];
	char *n_str_point = (char *) malloc(size + 1); //��Ϊmalloc���ص�ָ������Ϊֹ,������Ҫǿ��ת�� (char *)
	strcpy(n_str_point, str1); //���ַ���str1�������ַ�����

	//jstring jstr = (*env)->NewStringUTF(env,"����ַ���");//�����ı���  ��UTF-8ת��UTF
	//http://www.jianshu.com/p/333648d8a998  JNI��־������������  android jni ��������,����ô���
	//��Ҫ�ǻ������� .c�ļ�д���ĵĻ� �㱣���utf-8   Ҫ���Ĵ�c�ļ�����Ϊutf-8
	jstring jstr = (*env)->NewStringUTF(env, "english"); //�����ı���  ��UTF-8ת��UTF
	char *outStr;
	outStr = (*env)->GetStringUTFChars(env, jstr, NULL);
//	LOGI("%s",outStr);//��������ת��Ϊjni���jstring��ת��Ϊc�е��ַ������,��Ȼ������
//	LOGI("%s",str1);//����ַ���
//	LOGI("%s",str2);
//
//	LOGI("%s","����ַ�������");
//	LOGI("%d",strlen(str1));//����ַ�������
//	LOGI("%d",strlen(str2));
//
//	LOGI("%s","�������֮������ַ���");
//	LOGI("%s",n_str_point);//�������֮������ַ���
//	LOGI("%d",strlen(n_str_point));
//
//	LOGI("%s","���ƴ��֮������ַ���");
	strcat(n_str_point, str2); //����ԭ��char *strcat(char *dest, const char *src);
//	LOGI("%s",n_str_point);//�������֮������ַ���
//	LOGI("%d",strlen(n_str_point)); //strlen���س���������һ��\n���� http://www.jianshu.com/p/7fa9f615ee49

	jstring result = (*env)->NewStringUTF(env, n_str_point);

	//ɾ���ոն�̬������ڴ� ���������ڴ�й©
	//delete[] n_char;//C++
	free(n_str_point); //ע��ֻ���ͷŶ�̬������ڴ�
	//free() ֻ���ͷŶ�̬������ڴ�ռ䣬�������ͷ�������ڴ档�����д���Ǵ����
	//int a[10];
	// ...
	//free(a);

	//�ͷ�ָ��  ���� http://blog.csdn.net/xyang81/article/details/42066665
	(*env)->ReleaseStringUTFChars(env, instringA, str1); //ǰ����jdata������cdata
	(*env)->ReleaseStringUTFChars(env, instringB, str2);

	return result; //��Ҫת��Ϊ�м��jstring����
}

/*
 * Class:     com_example_testndkeclipse_JniClient
 * Method:    TestDataTypeJ2C
 * Signature: (SIJFDCZBLjava/lang/String;Ljava/lang/Object;Lcom/example/testndkeclipse/MyJavaClass;)V
 */
JNIEXPORT void JNICALL Java_com_example_testndkeclipse_JniClient_TestDataTypeJ2C(
		JNIEnv * env, jclass mJclass, jshort mJshort, jint mJint, jlong mJlong,
		jfloat mJfloat, jdouble mJdouble, jchar mJchar, jboolean mJboolean,
		jbyte mJbyte, jstring mJstring, jintArray mJintArray, jobject mJobject,
		jobject mJobjectClass)

{
	// %d �з���10��������%ld ������%hd������ %md,mָ����������ֶεĿ��
	// printf("s=%hd, i=%d, l=%ld, f=%f, d=%lf, c=%c, z=%c, b=%d", s, i, l, f, d, c, z, b);
	//short s, int i, long l, float f,double d, char c, boolean z, byte b
	LOGI("mJshort==>%hd\n", mJshort);
	LOGI("mJint==>%d\n", mJint);
	LOGI("mJlong==>%l\n", mJlong);
	LOGI("mJfloat==>%f\n", mJfloat);
	LOGI("mJdouble==>%lf\n", mJdouble);
	LOGI("mJchar==>%c\n", mJchar);
	LOGI("mJboolean==>%d\n", mJboolean);
	LOGI("mJbyte==>%d\n", mJbyte);
	//������������
	//jclass mJclass, jshort mJshort, jint mJint, jlong mJlong, jfloat mJfloat,
	//jdouble mJdouble, jchar mJchar, jboolean mJboolean, jbyte mJbyte

	//��������
	//jstring mJstring,
	//jintArray mJintArray
}

/*
 * Class:     com_example_testndkeclipse_JniClient
 * Method:    sumArray
 * Signature: ([I)[I
 *
 * ʵ���������
 */
JNIEXPORT jintArray JNICALL Java_com_example_testndkeclipse_JniClient_sumArray(
		JNIEnv * env, jclass mJclass, jintArray mjintArray) {

	jint cSum, cLen = 0;
	//1.��ȡ���鳤��
	cLen = (*env)->GetArrayLength(env, mjintArray);
	//2.�������鳤�Ⱥ�����Ԫ�ص���������������java����Ԫ�صĻ�����

	//��jarrayת��Ϊc�ɲ���������
//	jint* cPArray = (jint*) malloc(sizeof(jint) * cLen);
//	if (cPArray == NULL)
//		return NULL; //���������ڴ�ռ�ʧ��
//	//3.��ʼ���ڴ��� http://www.jianshu.com/p/cb8a3c004563
//	memset(cPArray, 0, sizeof(jint) * cLen);
//	LOGI("cLen==length>%d\n", cLen);
//	LOGI("cLen==sizeof>%d\n", sizeof(jint)*cLen);
//	//4. ����Java�����е�����Ԫ�ص���������
//	(*env)->GetIntArrayRegion(env, mjintArray, 0, cLen, cPArray); //�õ����鷽ʽ1  �����ݷ��ڻ�����

	// ���������е�Ԫ�����ڴ����ǲ������ģ�JVM���ܻḴ������ԭʼ���ݵ���������Ȼ�󷵻������������ָ��
	jint* cPArray = (*env)->GetIntArrayElements(env, mjintArray, NULL);
	if (cPArray == NULL) {
		return 0; // JVM����ԭʼ���ݵ�������ʧ��
	}

	jint i;
	for (i = 0; i < cLen; i++) { //�������
		cSum = cSum + cPArray[i];
	}
	LOGI("jSum==>%d\n", cSum);

	//��java�㷵�����鷽ʽ1
	jint cInts[cLen]; //����һ������
	for (i = 0; i < cLen; i++) {
		cInts[i] = cPArray[i];
	}
	//length =  sizeof(array) / sizeof(array[0]);  c/c++�������鳤��
	jintArray result;
	result = (*env)->NewIntArray(env, cLen);
	if (result == NULL) {
		return NULL; /* out of memory error thrown */
	}
	//move from the temp structure to the java structure  ��native����ת��Ϊjava������
	(*env)->SetIntArrayRegion(env, result, 0, sizeof(cInts) / sizeof(cInts[0]),
			cInts);

	(*env)->ReleaseIntArrayElements(env, mjintArray, cPArray, 0); // �ͷſ��ܸ��ƵĻ�����
	return result;
}

/*
 * Class:     com_example_testndkeclipse_JniClient
 * Method:    getArrayObjectFromC
 * Signature: (I)[[I
 *
 * C����һ����ά��������java
 */
JNIEXPORT jobjectArray JNICALL Java_com_example_testndkeclipse_JniClient_getArrayObjectFromC(
		JNIEnv * env, jclass mJclass, jint mJlen) {
	jobjectArray jObjectArrayResult; //jni�ж�ά����Ϊ����
	jclass jClassArray;
	//���һ��int�Ͷ�ά�����һ������
	jClassArray = (*env)->FindClass(env, "[I");
	if (jClassArray == NULL) { //out of memery
		return NULL;
	}
	// 2.����һ�������������ÿ��Ԫ����clsIntArray��ʾ��  ���� JNIEnv*, jsize, jclass, jobject
	jObjectArrayResult = (*env)->NewObjectArray(env, mJlen, jClassArray, NULL);
	if (jObjectArrayResult == NULL) {
		return NULL;
	}
	//Ϊ����Ԫ�ظ�ֵ
	jint i;
	for (i = 0; i < mJlen; i++) {
		jintArray mJintArray; //����һ��һά����
		//(*env)->GetIntArrayRegion(env,mJintArray,0,mJlen,NULL);//JNIEnv*, jintArray,jsize, jsize, jint*
		mJintArray = (*env)->NewIntArray(env, mJlen);
		if (mJintArray == NULL) {
			return NULL;
		}
		jint mBuff[mJlen - 1]; //����һ��һά��������
		jint j;
		for (j = 0; j < mJlen; j++) {
			mBuff[j] = i + j;
		}
		//����ת��
		(*env)->SetIntArrayRegion(env, mJintArray, 0, mJlen, mBuff); //JNIEnv*, jintArray,jsize, jsize, const jint*
		//�����������
		(*env)->SetObjectArrayElement(env, jObjectArrayResult, i, mJintArray); //JNIEnv*, jobjectArray, jsize, jobject
		(*env)->DeleteLocalRef(env, mJintArray); //JNIEnv*, jobject

	}
	return jObjectArrayResult;
}

/*
 * Class:     com_example_testndkeclipse_JniClient
 * Method:    callJavaStaticMethod
 * Signature: ()V
 *
 * ���е���java��ľ�̬����
 */
JNIEXPORT void JNICALL Java_com_example_testndkeclipse_JniClient_callJavaStaticMethod(
		JNIEnv * env, jclass cla) {
	jclass mJclass;
	jstring mJstring;
	jmethodID mJStaticmethodID;
	//1.��classpath·��������ClassMethod����࣬�����ظ����Class����
	int i = 0;
	mJclass = (*env)->FindClass(env, "com/example/testndkeclipse/MyJavaClass"); //JNIEnv*, const char*
	if (mJclass == NULL) {
		//LOGI("callJavaStaticMethod==>>mJclass==NULL==>>%s", "");
		return;
	}
	// 2����clazz���в���callStaticMethod����
	mJStaticmethodID = (*env)->GetStaticMethodID(env, mJclass,
			"callStaticMethod", "(Ljava/lang/String;I)V"); //JNIEnv*, jclass, const char*, const char*
	if (mJStaticmethodID == NULL) {
		printf("=====>>>can not foud callStaticMethod");
		return;
	}
	//3������clazz���callStaticMethod��̬����
	mJstring = (*env)->NewStringUTF(env, "==I am from C==");
	(*env)->CallStaticVoidMethod(env, mJclass, mJStaticmethodID, mJstring, 200); //JNIEnv*, jclass, jmethodID, ...

	// ɾ���ֲ�����
	(*env)->DeleteLocalRef(env, mJstring);
	(*env)->DeleteLocalRef(env, mJclass);

}

/*
 * Class:     com_example_testndkeclipse_JniClient
 * Method:    callJavaInstaceMethod
 * Signature: ()V
 *
 * ���е���java��Ķ��󷽷�
 */
JNIEXPORT void JNICALL Java_com_example_testndkeclipse_JniClient_callJavaInstaceMethod(
		JNIEnv * env, jclass jclazz) {
	jclass mJclass = NULL;
	jmethodID jmethodID_Construct; //���췽��ID
	jmethodID jmethodID_Method_Instance; //������ID
	jobject jobjectMyClass; //���ʵ��
	//1����classpath·��������ClassMethod����࣬�����ظ����Class����
	mJclass = (*env)->FindClass(env, "com/example/testndkeclipse/MyJavaClass");
	if (mJclass == NULL) {
		printf("====FindClass  not found \n");
		return;
	}
	// 2����ȡ���Ĭ�Ϲ��췽��ID
	jmethodID_Construct = (*env)->GetMethodID(env, mJclass, "<init>", "()V");
	if (jmethodID_Construct == NULL) {
		printf("GetMethodID not found ==>>jmethodID_Construct");
		return;
	}
	// 3������ʵ��������ID
	jmethodID_Method_Instance = (*env)->GetMethodID(env, mJclass,
			"callInstanceMethod", "(Ljava/lang/String;I)V");
	if (jmethodID_Method_Instance == NULL) {
		return;
	}
	// 4�����������ʵ��  �����޲ι��췽��  ����������췽��,����ɴ�����
	jobjectMyClass = (*env)->NewObject(env, mJclass, jmethodID_Construct); //JNIEnv*, jclass, jmethodID, ...
	if (jobjectMyClass == NULL) {
		printf("��com.example.testndkeclipse.MyJavaClass �����Ҳ���callInstanceMethod����");
		return;
	}
	// 5�����ö����ʵ������
	//jstring mJstring = (*env)->NewStringUTF(env,"==������Native,ͨ������java���󷽷�����==");
	jstring mJstring = (*env)->NewStringUTF(env,"==I am from Native==");
	(*env)->CallVoidMethod(env,jobjectMyClass,jmethodID_Method_Instance,mJstring,201);//JNIEnv*, jobject, jmethodID, ...

	 // ɾ���ֲ�����
	(*env)->DeleteLocalRef(env,mJstring);
	(*env)->DeleteLocalRef(env,jobjectMyClass);
	(*env)->DeleteLocalRef(env,jmethodID_Method_Instance);
	(*env)->DeleteLocalRef(env,jmethodID_Construct);
}

#ifdef __cplusplus
}
#endif
