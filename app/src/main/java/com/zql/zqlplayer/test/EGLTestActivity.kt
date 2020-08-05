package com.zql.zqlplayer.test

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.zql.zqlplayer.R
import com.zql.zqlplayer.opengl.NativeOpengl

import kotlinx.android.synthetic.main.activity_e_g_l_test.*

class EGLTestActivity : AppCompatActivity() {

    private val nativeOpengl = NativeOpengl()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_e_g_l_test)
        surface_view.nativeOpengl = nativeOpengl
        changeProgram.setOnClickListener {
            nativeOpengl.changeOpenglProgram();
        }
    }

}
