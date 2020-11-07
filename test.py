import datetime

with open("/tmp/CSRBvfsOverlayTestText.txt", 'w+') as f:
    f.write(str(datetime.datetime.now()))

    f.seek(0)

    for l in f:
        print(l)

