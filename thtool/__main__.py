import argparse

from . import window

def main() -> None:
    parser = argparse.ArgumentParser(description="thtool(TouHouTool) : tools for TouHou project")

    parser.add_argument("--version", action="store_true", help="show version")

    parser.add_argument("--bind",
                        help="bind to window."
                            "[ --bind list ] print all windows' title; "
                            "[ --bind foreground ] bind to foreground window; "
                            "[ --bind guess ] bind to a window thtool guess; "
                            "[ --bind <title> ] bind to a window with title <title>")

    args = parser.parse_args()

    if args.version:
        print("thtool(TouHouTool) v0.0.0")

    if args.bind == "list":
        window.print_all_windows()
    elif args.bind == "foreground":
        window.set_hwnd_foreground()
    # elif args.bind == "guess":
    #     window.set_hwnd_guess()
    # elif args.bind:
    #     window.set_hwnd_title(args.bind)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("Keyborad interrupt!")
else:
    raise RuntimeError("This file is not intended to be imported!")