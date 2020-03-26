import pexpect

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_1_elev.xml")
hiss.expect(".*Average waiting time: +57.86")
hiss.expect(".*Average traveling time: +29.01")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_2_elev.xml")
hiss.expect(".*Average waiting time: +25.57")
hiss.expect(".*Average traveling time: +13.61")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss standard_1_elev.xml")
hiss.expect(".*Average waiting time: +23.51")
hiss.expect(".*Average traveling time: +14.15")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss standard_2_elev.xml")
hiss.expect(".*Average waiting time: +14.67")
hiss.expect(".*Average traveling time: +12.26")
