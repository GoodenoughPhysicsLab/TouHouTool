import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="thtool(TouHouTool) : tools for TouHou project")

    parser.add_argument("--version", dest="version", help="show version")

    args = parser.parse_args()
    if args.version:
        print("thtool(TouHouTool) v0.0.0")