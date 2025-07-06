// Package.swift
// swift-tools-version:5.6
import PackageDescription

let package = Package(
    name: "SGuitar",
    platforms: [
        .iOS(.v14),
    ],
    products: [
        .library(
            name: "SGuitar",
            targets: ["SGuitar"]
        ),
    ],
    targets: [
        .binaryTarget(
            name: "SGuitar",
            url: "https://github.com/jbsohn/SGuitar/releases/download/v0.0.12/SGuitar.xcframework.zip",
            checksum: "4864082ae444e89b6443f7a587b10654e87cc005a6cbff8d93c3a3874f886d94"
        )
    ]
)
