import org.jetbrains.kotlin.gradle.ExperimentalKotlinGradlePluginApi
import org.jetbrains.kotlin.gradle.dsl.JvmTarget

plugins {
    alias(libs.plugins.kotlinMultiplatform)
    alias(libs.plugins.androidLibrary)
    id("module.publication")
}

kotlin {
  listOf(
    iosArm64(),
    iosX64(),
    iosSimulatorArm64()
  ).forEach {
    it.binaries.framework {
      baseName = "SGuitar"
      binaryOption("bundleId", "com.steelsidekick.SGuitar")
    }
  }
}

android {
  namespace = "org.jetbrains.kotlinx.multiplatform.library.template1"
  compileSdk = libs.versions.android.compileSdk.get().toInt()
  defaultConfig {
    minSdk = libs.versions.android.minSdk.get().toInt()
  }
}
