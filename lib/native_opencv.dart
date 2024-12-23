import 'native_opencv_platform_interface.dart';
import 'dart:ffi' as ffi;
import 'dart:io';
import 'package:ffi/ffi.dart';

class NativeOpencv {
  Future<String?> getPlatformVersion() {
    return NativeOpencvPlatform.instance.getPlatformVersion();
  }
}

// C function signatures
typedef _CVersionFunc = ffi.Pointer<Utf8> Function();
typedef _CProcessImageFunc = ffi.Int32 Function(
  ffi.Int32,
  ffi.Int32,
  ffi.Pointer<Utf8>,
  ffi.Pointer<ffi.Uint8>,
  ffi.Pointer<ffi.Uint8>,
  ffi.Pointer<ffi.Uint8>,
  ffi.Pointer<ffi.Uint8>,
);

// Dart function signatures
typedef _VersionFunc = ffi.Pointer<Utf8> Function();
typedef _ProcessImageFunc = int Function(
  int,
  int,
  ffi.Pointer<Utf8>,
  ffi.Pointer<ffi.Uint8>,
  ffi.Pointer<ffi.Uint8>,
  ffi.Pointer<ffi.Uint8>,
  ffi.Pointer<ffi.Uint8>,
);

// Getting a library that holds needed symbols
ffi.DynamicLibrary _openDynamicLibrary() {
  if (Platform.isAndroid) {
    return ffi.DynamicLibrary.open('libnative_opencv.so');
  } else if (Platform.isWindows) {
    return ffi.DynamicLibrary.open("native_opencv_windows_plugin.dll");
  }

  return ffi.DynamicLibrary.process();
}

ffi.DynamicLibrary _lib = _openDynamicLibrary();

// Looking for the functions
final _VersionFunc _version =
    _lib.lookup<ffi.NativeFunction<_CVersionFunc>>('version').asFunction();
final _ProcessImageFunc _processImage = _lib
    .lookup<ffi.NativeFunction<_CProcessImageFunc>>('processing')
    .asFunction();

String opencvVersion() {
  return _version().toDartString();
}

int processImage(ProcessImageArguments args) {
  return _processImage(args.height, args.width, args.input.toNativeUtf8(),
      args.grayScale, args.filtered, args.negative, args.DM);
}

class ProcessImageArguments {
  int height;
  int width;
  final String input;
  ffi.Pointer<ffi.Uint8> grayScale;
  ffi.Pointer<ffi.Uint8> filtered;
  ffi.Pointer<ffi.Uint8> negative;
  ffi.Pointer<ffi.Uint8> DM;

  ProcessImageArguments(this.height, this.width, this.input, this.grayScale,
      this.filtered, this.negative, this.DM);
}
