import time
import argparse
import cv2
from . import prints
from . import window
from . import scene
from . import kb_control

def main() -> None:
    parser = argparse.ArgumentParser(description="thtool(TouHouTool) : tools for TouHou project")

    parser.add_argument("--version", action="store_true", help="show version")

    parser.add_argument("--bind",
                        help="bind to window."
                            "[ --bind list ] print all windows' title; "
                            "[ --bind list-guess ] print all guessed windows' title; "
                            "[ --bind foreground ] bind to foreground window; "
                            "[ --bind guess ] bind to a window thtool guessed; "
                            "[ --bind <title> ] bind to a window with title <title>")

    args = parser.parse_args()

    if args.version:
        print("thtool(TouHouTool) v0.0.0")

    if args.bind == "list":
        window.print_all_windows()
        exit(0)
    elif args.bind == "list-guess":
        window.print_all_windows(only_guess=True)
        exit(0)
    elif args.bind == "foreground":
        window.bind_foreground()
    elif args.bind == "guess":
        window.bind_guess()
    elif args.bind:
        window.bind_title(args.bind)
    else:
        raise window.BindError("you must bind to a TouHou window")

    window.init_Gdiplus()
    try:
        while True:
            img = scene.get_scene()
            # kb_control.send(kb_control.Behavior.bomb)
            # time.sleep(1)
    except window.BindError: # window closed
        print("Find touhou window closed")
        exit(0)
    finally:
        cv2.destroyAllWindows()
        window.free_Gdiplus()


if __name__ == '__main__':
    try:
        prints.enable_win32_ansi()
        main()
    except KeyboardInterrupt:
        print("Keyboard interrupt!")
else:
    raise RuntimeError("This file is not intended to be imported!")