@attrib +r ..\..\..\epoc32\release\winscw\udeb\z\sys\data\estart_old.txt
@copy /y ..\..\..\epoc32\release\winscw\udeb\z\sys\data\estart.txt ..\..\..\epoc32\release\winscw\udeb\z\sys\data\estart_old.txt
@attrib +r ..\..\..\epoc32\release\winscw\udeb\z\sys\data\estart_old.txt
@attrib -r ..\..\..\epoc32\release\winscw\udeb\z\sys\data\estart.txt
@copy /y ..\..\..\epoc32\release\winscw\udeb\z\sys\data\estart_mds_ms.txt ..\..\..\epoc32\release\winscw\udeb\z\sys\data\estart.txt
@rem
@copy /y ..\..\..\epoc32\release\winscw\udeb\platformenv.dll ..\..\..\epoc32\release\winscw\udeb\platformenv_old.dll
@attrib +r ..\..\..\epoc32\release\winscw\udeb\platformenv_old.dll
@attrib -r ..\..\..\epoc32\release\winscw\udeb\platformenv.dll
@copy /y ..\..\..\epoc32\release\winscw\udeb\platformenv_ms.dll ..\..\..\epoc32\release\winscw\udeb\platformenv.dll