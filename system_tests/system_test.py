import pexpect

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_1_elev.xml")
hiss.expect(".*Average waiting time: +80.34")
hiss.expect(".*Average traveling time: +45.6")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_2_elev.xml")
hiss.expect(".*Average waiting time: +33.42")
hiss.expect(".*Average traveling time: +19.5")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss standard_1_elev.xml")
hiss.expect(".*Average waiting time: +23.19")
hiss.expect(".*Average traveling time: +17.45")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss standard_2_elev.xml")
hiss.expect(".*Average waiting time: +15.78")
hiss.expect(".*Average traveling time: +15.87")
