package com.example.atelier9_telechargerimage

import android.graphics.Bitmap
import android.os.Bundle
import android.os.Environment
import android.view.View
import android.widget.EditText
import android.widget.ImageView
import android.widget.LinearLayout
import androidx.appcompat.app.AppCompatActivity
import com.android.volley.Request
import com.android.volley.Response
import com.android.volley.toolbox.ImageRequest
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley
import com.google.android.material.snackbar.Snackbar
import java.util.regex.Pattern


class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun download(v : View) {

        val queue = Volley.newRequestQueue(this)
        val urlEdit : EditText = findViewById(R.id.tvURL)
        val url = urlEdit.text.toString()
        var responseText: String = ""
        val allUrl: MutableList<String> = ArrayList()

        val stringRequest = StringRequest(
            // Requête get
            Request.Method.GET,
            // l'URL
            url,
            Response.Listener { response ->
                val imgRegex = "(?i)<img[^>]+?src\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>"

                val p = Pattern.compile(imgRegex)
                val m = p.matcher(response)

                while (m.find()) {
                    var imgSrc = m.group(1)
                    val base = Environment.getExternalStorageDirectory().absolutePath.toString() + "/tanadgomaaa"
                    val imagePath = "file://$base/test.jpg"
                    imgSrc = imgSrc.replace(imgSrc, imagePath)
                    allUrl.add(imgSrc)
                }
            },
            Response.ErrorListener { erreur ->
                responseText =  "Erreur de téléchargement " + erreur.toString()
            }
        )

        // On émet la requête
        queue.add(stringRequest)


        var imgUrl: String
        var mCLayout : LinearLayout = findViewById (R.id.viewLayout);

        for (urlImage in allUrl.indices) {
            imgUrl = urlImage.toString()

            var imageRequest = ImageRequest(
                imgUrl,  // Image URL
                { response ->
                    // Bitmap listener
                    // Do something with response
                    val view: ImageView = ImageView(this);
                    view.setImageBitmap(response)

                    // Save this downloaded bitmap to internal storage
                    //val uri: Uri = saveImageToInternalStorage(response)

                    // Display the internal storage saved image to image view
                    //mImageViewInternal.setImageURI(uri)
                },
                0,  // Image width
                0,  // Image height
                ImageView.ScaleType.CENTER_CROP,  // Image scale type
                Bitmap.Config.RGB_565
            )  //Image decode configuration
            { error ->
                // Error listener
                // Do something with error response
                error.printStackTrace()
                Snackbar.make(mCLayout, "Error", Snackbar.LENGTH_LONG).show()
            }

            queue.add(imageRequest)
        }

    }
}