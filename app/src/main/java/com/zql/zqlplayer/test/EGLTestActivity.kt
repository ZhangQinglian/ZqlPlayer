package com.zql.zqlplayer.test

import android.graphics.BitmapFactory
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import com.zql.zqlplayer.R
import com.zql.zqlplayer.opengl.NativeOpengl

import kotlinx.android.synthetic.main.activity_e_g_l_test.*
import java.nio.ByteBuffer

class EGLTestActivity : AppCompatActivity() {

    private val nativeOpengl = NativeOpengl()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_e_g_l_test)
        surface_view.nativeOpengl = nativeOpengl
    }

}
