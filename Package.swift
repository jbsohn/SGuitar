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
            url: "https://github.com/jbsohn/SGuitar/releases/download/v0.0.6/SGuitar.xcframework.zip",
            checksum: "f9270bae8465a9ea1bf929062d942e096433c30cf04d54ebf2422c381ad10d1e"
        )
    ]
)
