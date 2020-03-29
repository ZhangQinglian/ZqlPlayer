package com.zql.zqlplayer

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.zql.zqlplayer.test.EGLTestActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        btn_to_egl_test.setOnClickListener {
            startActivity(Intent(applicationContext, EGLTestActivity::class.java))
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
