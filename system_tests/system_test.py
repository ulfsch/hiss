import pexpect

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_1_elev.xml")
hiss.expect(".*Average waiting time: +21.34")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss trivial_2_elev.xml")
hiss.expect(".*Average waiting time: +5.32")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss config_1_elev.xml")
hiss.expect(".*Average waiting time: +10.78")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss config_2_elev.xml")
hiss.expect(".*Average waiting time: +3.28")
hiss.expect(".*Average traveling time: +5.18")
