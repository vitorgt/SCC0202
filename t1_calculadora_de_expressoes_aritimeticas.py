import sys

for line in sys.stdin:
    try:
        print("%.2f" % eval(line.replace(";", "").replace(",", "")))
    except Exception:
        print("Expressao incorreta")
