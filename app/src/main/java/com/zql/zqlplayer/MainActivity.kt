package com.zql.zqlplayer

import android.Manifest
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.core.app.ActivityCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import com.zql.zqlplayer.test.EGLTestActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestPermissions()
        initMenus()
    }

    private fun initMenus() {
        val adapter = MenuListAdapter()
        adapter.menuCallback = object : MenuListAdapter.MenuCallback {
            override fun onMenuClick(position: Int) {
                when (position) {
                    0 -> {
                        startActivity(Intent(applicationContext, EGLTestActivity::class.java))
                    }
                }
            }
        }
        val layoutManager = LinearLayoutManager(
            this,
             LinearLayoutManager.VERTICAL,
            false
        )
        menu_list.adapter = adapter
        menu_list.layoutManager = layoutManager
        adapter.notifyDataSetChanged()
    }

    private fun requestPermissions() {
        ActivityCompat.requestPermissions(
            this,
            arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE),
            23333
        )
    }

    class MenuListAdapter : RecyclerView.Adapter<MenuHolder>() {

        interface MenuCallback {
            fun onMenuClick(position: Int)
        }

        private val menus = arrayListOf("EGL 环境测试")

        var menuCallback: MenuCallback? = null
        override fun onCreateViewHolder(view: ViewGroup, position: Int): MenuHolder {

            val view = LayoutInflater.from(view.context).inflate(R.layout.item_menu, view, false)
            return MenuHolder(view, menuCallback)
        }

        override fun getItemCount(): Int = menus.size

        override fun onBindViewHolder(holder: MenuHolder, position: Int) {
            holder.bind(menus[position])
        }

    }

    class MenuHolder(view: View, private val callback: MenuListAdapter.MenuCallback?) :

        RecyclerView.ViewHolder(view) {

        fun bind(menuText: String) {
            itemView.findViewById<TextView>(R.id.menu_text)?.apply {
                text = menuText
            }
            itemView.setOnClickListener {
                callback?.onMenuClick(adapterPosition)

            }
        }
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}
