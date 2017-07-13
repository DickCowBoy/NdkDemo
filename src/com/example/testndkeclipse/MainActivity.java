package com.example.testndkeclipse;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener {

	private Button bt1, bt2, bt3,bt4, bt5, bt6,bt7,bt8,bt9,bt10;
	static {
		// ����so��
		System.loadLibrary("TestNdk");// lib��.soΪǰ׺��׺,���ü���
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		findViews();
		// String strFromC = JniClient.AddStr("Java2C_����1", "Java2C_����2");

	}

	private void findViews() {
		// TODO Auto-generated method stub
		bt1 = (Button) this.findViewById(R.id.bt1);
		bt1.setOnClickListener(this);
		bt2 = (Button) this.findViewById(R.id.bt2);
		bt2.setOnClickListener(this);
		bt3 = (Button) this.findViewById(R.id.bt3);
		bt3.setOnClickListener(this);
		bt4 = (Button) this.findViewById(R.id.bt4);
		bt4.setOnClickListener(this);
		bt5 = (Button) this.findViewById(R.id.bt5);
		bt5.setOnClickListener(this);
		bt6 = (Button) this.findViewById(R.id.bt6);
		bt6.setOnClickListener(this);
		bt7 = (Button) this.findViewById(R.id.bt7);
		bt7.setOnClickListener(this);
		bt8 = (Button) this.findViewById(R.id.bt8);
		bt8.setOnClickListener(this);
		bt9 = (Button) this.findViewById(R.id.bt9);
		bt9.setOnClickListener(this);
		bt10 = (Button) this.findViewById(R.id.bt10);
		bt10.setOnClickListener(this);
	}

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if (v == bt1) {
			//�����
			Uri uri = Uri
					.parse("http://blog.csdn.net/e_inch_photo/article/details/74923317");
			Intent intent = new Intent(Intent.ACTION_VIEW, uri);
			startActivity(intent);
		} else if (v == bt2) {
			//���Log��ӡ��logcat
			Uri uri = Uri
					.parse("http://blog.csdn.net/e_inch_photo/article/details/74926529");
			Intent intent = new Intent(Intent.ACTION_VIEW, uri);
			startActivity(intent);
		} else if (v == bt3) {
			//Android NDK�������֪ʶ����
			Uri uri = Uri
					.parse("http://www.jianshu.com/p/e7a765691067");
			Intent intent = new Intent(Intent.ACTION_VIEW, uri);
			startActivity(intent);
			
			String strFromC = JniClient.AddStr("Java2C_����1", "Java2C_����2");
			bt3.setText(strFromC);
		}else if (v == bt4) {
			short s = 1;
			int i = 10;
			long l= 100;
			float f=  1000.00f;
			boolean z = true;
			int[] array = null;
			MyJavaClass mMyJavaClass = null;
			Object obj = null;
			String str = null;
			double d = 10000.000;
			byte b = 1;
			char c = 60;
			//JNI ���������� Java �������͵�ӳ���ϵ  http://wiki.jikexueyuan.com/project/jni-ndk-developer-guide/relational.html
			JniClient.TestDataTypeJ2C(s, i, l, f, d, c, z, b, str, array, obj, mMyJavaClass);
		}else if (v == bt5) {
			//C�д���Java�д��ݵ��ַ���-�ַ������
			//
			String strFromC = JniClient.AddStr("Java2C_����1", "Java2C_����2");
			bt5.setText(bt5.getText()+strFromC);
		}else if (v == bt6) {
			//http://wiki.jikexueyuan.com/project/jni-ndk-developer-guide/array.html
			int[] javaArray = new int[]{10,20,30,40,50,60};
			//C�д���Java�д��ݵ��ַ���-�ַ������
			int[] javaArrayResult = JniClient.sumArray(javaArray );
			if (javaArrayResult!=null) {
				Toast.makeText(MainActivity.this, "native�з�������"+ javaArrayResult[0],Toast.LENGTH_SHORT).show();
			}
		}else if (v == bt7) {
			//http://wiki.jikexueyuan.com/project/jni-ndk-developer-guide/array.html
			
		}else if (v == bt8) {
			//http://wiki.jikexueyuan.com/project/jni-ndk-developer-guide/array.html
			
		}else if (v == bt9) {
			//http://wiki.jikexueyuan.com/project/jni-ndk-developer-guide/array.html
			
		}else if (v == bt10) {
			//http://wiki.jikexueyuan.com/project/jni-ndk-developer-guide/array.html
			
		}
	}

}
