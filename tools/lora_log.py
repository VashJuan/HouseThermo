# Log the M5Dial (COM13) and receiver (COM11) serial ports together, timestamped.
# Usage: python tools/lora_log.py <seconds> <out_dir>   (writes dial5.log, recv5.log)
import sys, time, serial
secs = float(sys.argv[1]); outdir = sys.argv[2]
ports = {"COM13": "dial5.log", "COM11": "recv5.log"}
conns = {}
for p, name in ports.items():
    s = serial.Serial(); s.port = p; s.baudrate = 115200; s.timeout = 0
    s.dtr = False; s.rts = False; s.open()
    conns[p] = (s, open(f"{outdir}/{name}", "wb"))
t0 = time.time()
while time.time() - t0 < secs:
    for p, (s, f) in conns.items():
        try:
            d = s.read(4096)
        except serial.SerialException:
            continue
        if d:
            # prefix each chunk with elapsed seconds so the two logs line up
            f.write(f"\n[{time.time() - t0:7.1f}] ".encode() + d); f.flush()
    time.sleep(0.05)
