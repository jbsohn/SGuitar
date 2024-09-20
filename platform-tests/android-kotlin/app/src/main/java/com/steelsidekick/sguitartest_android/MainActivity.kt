package com.steelsidekick.sguitartest_android

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.steelsidekick.sguitartest_android.ui.theme.SGuitarTestAndroidTheme
import com.steelsidekick.sguitar.Note
import com.steelsidekick.sguitar.NoteValue
import com.steelsidekick.sguitar.Scale

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            SGuitarTestAndroidTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = "Android",
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    val n = Note(48)
    val s = Scale(NoteValue.C, listOf(2, 2, 1, 2, 2, 2))
    Column {
        Text(
            text = "Note: ${n.getNote().nameSharp()}",
            modifier = modifier
        )
        Text(
            text = "Scale: ${s.testDescription()}",
            modifier = modifier
        )
    }
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    SGuitarTestAndroidTheme {
        Greeting("Android")
    }
}