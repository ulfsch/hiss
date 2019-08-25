import pexpect

hiss = pexpect.spawn("../cmake-build-debug/src/hiss config_1_elev.xml")
hiss.expect(".*Average waiting time: +9.99")

hiss = pexpect.spawn("../cmake-build-debug/src/hiss config_2_elev.xml")
hiss.expect(".*Average waiting time: +5.73")

