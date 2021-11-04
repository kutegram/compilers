@echo off
Echo Switching emulator to Application Shell start

attrib -r \epoc32\release\winscw\udeb\z\resource\starter.rsc
attrib -r \epoc32\release\winscw\urel\z\resource\starter.rsc
attrib -r \epoc32\release\winscw\udeb\z\resource\starter_non_critical_1.rsc
attrib -r \epoc32\release\winscw\urel\z\resource\starter_non_critical_1.rsc

copy \epoc32\data\z\resource\starter_shell.rsc	\epoc32\release\winscw\udeb\z\resource\starter.rsc
copy \epoc32\data\z\resource\starter_shell.rsc	\epoc32\release\winscw\urel\z\resource\starter.rsc
copy \epoc32\data\z\resource\starter_non_critical_1_shell.rsc	\epoc32\release\winscw\udeb\z\resource\starter_non_critical_1.rsc
copy \epoc32\data\z\resource\starter_non_critical_1_shell.rsc	\epoc32\release\winscw\urel\z\resource\starter_non_critical_1.rsc
