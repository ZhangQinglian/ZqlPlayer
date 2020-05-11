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

        val bitmap = BitmapFactory.decodeResource(resources, R.drawable.one_piece)
        val buffer = ByteBuffer.allocate(bitmap.height * bitmap.width * 4)
        bitmap.copyPixelsToBuffer(buffer)
        buffer.flip()
        val pixels = buffer.array()
        nativeOpengl.imgData(bitmap.width, bitmap.height, pixels.size, pixels)
    }

}
