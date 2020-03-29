package com.zql.zqlplayer.test

import android.content.Context
import android.util.AttributeSet
import android.view.SurfaceHolder
import android.view.SurfaceView
import com.zql.zqlplayer.opengl.NativeOpengl

/**
 *    @author 番茄沙司 2020/3/29
 */
class EglTestSurfaceView : SurfaceView, SurfaceHolder.Callback {

    var nativeOpengl: NativeOpengl? = null

    constructor(context: Context) : super(context) {
    }

    constructor(context: Context, attributeSet: AttributeSet) : super(context, attributeSet) {
    }

    constructor(context: Context, attributeSet: AttributeSet, defStyleAttr: Int) : super(
        context,
        attributeSet,
        defStyleAttr
    ) {
    }

    init {
        holder.addCallback(this)
    }

    override fun surfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {

    }

    override fun surfaceDestroyed(holder: SurfaceHolder?) {
        nativeOpengl?.surfaceDestory()
    }

    override fun surfaceCreated(holder: SurfaceHolder?) {
        holder?.surface?.let {
            nativeOpengl?.surfaceCreate(it)
        }
    }
}