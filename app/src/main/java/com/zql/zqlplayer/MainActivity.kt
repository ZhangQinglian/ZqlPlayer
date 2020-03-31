package com.zql.zqlplayer

import android.Manifest
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.app.ActivityCompat
import com.zql.zqlplayer.test.EGLTestActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestPermissions()
        btn_to_egl_test.setOnClickListener {
            startActivity(Intent(applicationContext, EGLTestActivity::class.java))
        }
    }

    private fun requestPermissions() {
        ActivityCompat.requestPermissions(
            this,
            arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE),
            23333
        )
    }

    companion object {

        init {
            System.loadLibrary("native-lib")
        }
    }
}
