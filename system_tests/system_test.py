import pexpect

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_1_elev.xml")
hiss.expect(".*Average waiting time: +57.86")
hiss.expect(".*Average traveling time: +29.01")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_2_elev.xml")
hiss.expect(".*Average waiting time: +25.41")
hiss.expect(".*Average traveling time: +11.78")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss standard_1_elev.xml")
hiss.expect(".*Average waiting time: +23.67")
hiss.expect(".*Average traveling time: +15.55")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss standard_2_elev.xml")
hiss.expect(".*Average waiting time: +14.04")
hiss.expect(".*Average traveling time: +12.85")
