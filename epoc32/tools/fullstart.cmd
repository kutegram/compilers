@echo off
Echo Switching emulator to normal start

attrib -r \epoc32\release\winscw\udeb\z\resource\starter.rsc
attrib -r \epoc32\release\winscw\urel\z\resource\starter.rsc
attrib -r \epoc32\release\winscw\udeb\z\resource\starter_non_critical_1.rsc
attrib -r \epoc32\release\winscw\urel\z\resource\starter_non_critical_1.rsc

copy \epoc32\data\z\resource\starter.rsc	\epoc32\release\winscw\udeb\z\resource\starter.rsc
copy \epoc32\data\z\resource\starter.rsc	\epoc32\release\winscw\urel\z\resource\starter.rsc
copy \epoc32\data\z\resource\starter_non_critical_1.rsc	\epoc32\release\winscw\udeb\z\resource\starter_non_critical_1.rsc
copy \epoc32\data\z\resource\starter_non_critical_1.rsc	\epoc32\release\winscw\urel\z\resource\starter_non_critical_1.rsc
