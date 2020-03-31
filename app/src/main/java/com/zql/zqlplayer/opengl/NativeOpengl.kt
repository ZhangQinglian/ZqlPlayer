package com.zql.zqlplayer.opengl

import android.view.Surface

/**
 *    @author 番茄沙司 2020/3/29
 */
public class NativeOpengl {

    external fun surfaceCreate(surface: Surface): Unit
    external fun surfaceChanged(width: Int, height: Int)
    external fun surfaceDestroy()
}