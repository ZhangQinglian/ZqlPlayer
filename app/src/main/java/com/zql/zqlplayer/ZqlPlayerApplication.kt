package com.zql.zqlplayer

import android.app.Application
import com.tencent.bugly.crashreport.CrashReport

/**
 * @author 番茄沙司
 * created at 2020/3/31
 */
class ZqlPlayerApplication : Application() {
    override fun onCreate() {
        super.onCreate()
        CrashReport.initCrashReport(applicationContext, "25f573d869", false);
    }
}