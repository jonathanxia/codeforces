import os
import platform


def get_compiler():
    """C++ compiler command for local builds.

    On macOS, /usr/bin/g++ resolves to the selected Xcode's clang, which can be
    older than the installed SDK headers (e.g. Xcode 15 clang vs macOS 26 SDK)
    and fail to compile anything. Prefer the Command Line Tools clang with its
    matching SDK when both are present; fall back to plain g++ otherwise.
    """
    if platform.system() == "Darwin":
        clt = "/Library/Developer/CommandLineTools/usr/bin/clang++"
        sdk = "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
        if os.path.exists(clt) and os.path.exists(sdk):
            return f"{clt} -isysroot {sdk}"
    return "g++"
