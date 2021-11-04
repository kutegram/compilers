��    4      �  G   \      x  
  y  0  �  t  �  $   *    O  v  c     �     �       ,         M  %   k  ,   �  -   �      �  &        4     T     t     v     �  E   �     �     �  �   
  (   �     �  �   �  &   n     �     �     �     �     �  )   �  (        8     :     Y     u     �     �     �     �     �     �          (     ?     Z     k  0  z  |  �  ,  (  �  U  6   E#    |#  t  �$     �%     	&     "&  "   9&     \&     u&  "   �&  #   �&     �&     �&     '     1'     K'     M'     ^'  G   s'     �'     �'  �   �'  %   k(     �(  �   �(  /   P)     �)     �)     �)     �)     �)  '   �)  '   *     /*     1*  !   M*  !   o*     �*     �*     �*     �*      �*     �*     
+     &+     ?+     [+     l+     $                    /      ,      0      "               -   )   *   3          4                                                  &             2          '   %          !                1                     
       .   (   +   	   #                 
Context control:
  -B, --before-context=NUM  print NUM lines of leading context
  -A, --after-context=NUM   print NUM lines of trailing context
  -C, --context=NUM         print NUM lines of output context
  -NUM                      same as --context=NUM
      --color[=WHEN],
      --colour[=WHEN]       use markers to distinguish the matching string
                            WHEN may be `always', `never' or `auto'.
  -U, --binary              do not strip CR characters at EOL (MSDOS)
  -u, --unix-byte-offsets   report offsets as if CRs were not there (MSDOS)

`egrep' means `grep -E'.  `fgrep' means `grep -F'.
With no FILE, or when FILE is -, read standard input.  If less than
two FILEs given, assume -h.  Exit status is 0 if match, 1 if no match,
and 2 if trouble.
 
Miscellaneous:
  -s, --no-messages         suppress error messages
  -v, --invert-match        select non-matching lines
  -V, --version             print version information and exit
      --help                display this help and exit
      --mmap                use memory-mapped input if possible
 
Output control:
  -m, --max-count=NUM       stop after NUM matches
  -b, --byte-offset         print the byte offset with output lines
  -n, --line-number         print line number with output lines
      --line-buffered       flush output on every line
  -H, --with-filename       print the filename for each match
  -h, --no-filename         suppress the prefixing filename on output
      --label=LABEL         print LABEL as filename for standard input
  -o, --only-matching       show only the part of a line matching PATTERN
  -q, --quiet, --silent     suppress all normal output
      --binary-files=TYPE   assume that binary files are TYPE
                            TYPE is 'binary', 'text', or 'without-match'
  -a, --text                equivalent to --binary-files=text
  -I                        equivalent to --binary-files=without-match
  -d, --directories=ACTION  how to handle directories
                            ACTION is 'read', 'recurse', or 'skip'
  -D, --devices=ACTION      how to handle devices, FIFOs and sockets
                            ACTION is 'read' or 'skip'
  -R, -r, --recursive       equivalent to --directories=recurse
      --include=PATTERN     files that match PATTERN will be examined
      --exclude=PATTERN     files that match PATTERN will be skipped.
      --exclude-from=FILE   files that match PATTERN in FILE will be skipped.
  -L, --files-without-match only print FILE names containing no match
  -l, --files-with-matches  only print FILE names containing matches
  -c, --count               only print a count of matching lines per FILE
  -Z, --null                print 0 byte after FILE name
 
Report bugs to <bug-grep@gnu.org>.
   -E, --extended-regexp     PATTERN is an extended regular expression
  -F, --fixed-strings       PATTERN is a set of newline-separated strings
  -G, --basic-regexp        PATTERN is a basic regular expression
  -P, --perl-regexp         PATTERN is a Perl regular expression
   -e, --regexp=PATTERN      use PATTERN as a regular expression
  -f, --file=FILE           obtain PATTERN from FILE
  -i, --ignore-case         ignore case distinctions
  -w, --word-regexp         force PATTERN to match only whole words
  -x, --line-regexp         force PATTERN to match only whole lines
  -z, --null-data           a data line ends in 0 byte, not newline
 %s (GNU grep) %s
 %s: illegal option -- %c
 %s: invalid option -- %c
 %s: option `%c%s' doesn't allow an argument
 %s: option `%s' is ambiguous
 %s: option `%s' requires an argument
 %s: option `--%s' doesn't allow an argument
 %s: option `-W %s' doesn't allow an argument
 %s: option `-W %s' is ambiguous
 %s: option requires an argument -- %c
 %s: unrecognized option `%c%s'
 %s: unrecognized option `--%s'
 ' (standard input) Binary file %s matches
 Copyright 1988, 1992-1999, 2000, 2001 Free Software Foundation, Inc.
 Memory exhausted No syntax specified Search for PATTERN in each FILE or standard input.
Example: %s -i 'hello world' menu.h main.c

Regexp selection and interpretation:
 The -P and -z options cannot be combined The -P option is not supported This is free software; see the source for copying conditions. There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 Try `%s --help' for more information.
 Unbalanced ( Unbalanced ) Unbalanced [ Unfinished \ escape Unknown system error Usage: %s [OPTION]... PATTERN [FILE] ...
 Usage: %s [OPTION]... PATTERN [FILE]...
 ` conflicting matchers specified input is too large to count invalid context length argument invalid max count malformed repeat count memory exhausted out of memory recursive directory loop unfinished repeat count unknown binary-files type unknown devices method unknown directories method warning: %s: %s
 writing output Project-Id-Version: grep 2.5.1a
POT-Creation-Date: 2002-03-26 16:38+0100
PO-Revision-Date: 2005-03-04 09:08+0200
Last-Translator: Toomas Soome <Toomas.Soome@microlink.ee>
Language-Team: Estonian <et@li.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=iso-8859-15
Content-Transfer-Encoding: 8-bit
 
Konteksti kontroll:
  -B, --before-context=NUM  tr�ki NUM rida eelnevat konteksti
  -A, --after-context=NUM   tr�ki NUM rida j�rgnevat konteksti
  -C, --context[=NUM]       tr�ki NUM rida v�ljund konteksti
  -NUM                      sama, kui --context=NUM
      --color[=MILLAL],
      --colour[=MILLAL]     kasuta otsitava s�ne eristamiseks markereid
                            MILLAL v�ib olla `always', `never' v�i `auto'.
  -U, --binary              �ra eemalda rea l�pust CR s�mboleid (MSDOS)
  -u, --unix-byte-offsets   teata aadressid CR s�mboleid arvestamata (MSDOS)

`egrep' t�hendab `grep -E'.  `fgrep' t�hendab `grep -F'.
Kui FAIL pole antud v�i kui FAIL v��rtus on -, loeb standardsisendit. Kui on
antud v�hem kui kaks faili, eeldatakse v�tit -h. Kui muster leitakse,
l�petab programm t�� koodiga 0, kui ei leita, siis koodiga 1 ja
kui oli mingi muu probleem, siis koodiga 2.
 
Muud:
  -s, --no-messages         blokeeri veateated
  -v, --invert-match        vali mitte-sobivad read
  -V, --version             esita versiooniinfo ja l�peta t��
      --help                esita see abiinfo ja l�peta t��
      --mmap                kasuta kui v�imalik sisendi m�llu laadimist
 
V�ljundi kontroll:
  -m, --max-count=NUM       l�peta peale NUM leidu
  -b, --byte-offset         tr�ki baidi aadress v�ljundreale
  -n, --line-number         tr�ki rea number v�ljundreale
      --line-buffered       v�ljasta k�ik peale iga rida
  -H, --with-filename       tr�ki iga leiu failinimi
  -h, --no-filename         keela v�ljundis prefiks failinimi
  -q, --quiet, --silent     keela kogu tavap�rane v�ljund
      --binary-files=T��P   eeldab kahendfailide T��Pi
                            T��P on 'binary', 'text' v�i 'without-match'
  -a, --text                sama, kui --binary-files=text
  -I                        sama, kui --binary-files=without-match
  -d, --directories=TEGEVUS kuidas k�sitleda katalooge
                            TEGEVUS on 'read', 'recurse' v�i 'skip'
  -D, --devices=TEGEVUS     kuidas k�sitleda seadmeid, FIFO ja pistik faile
                            TEGEVUS on 'read' v�i 'skip'
  -R, -r, --recursive       sama, kui --directories=recurse
      --include=MUSTER      vaadeldakse mustrile MUSTER vastavaid faile
      --exclude=MUSTER      mustrile MUSTER vastavad failid j�etakse vahele
      --exclude-from=FAIL   mustrile failist FAIL vastavad failid
                            j�etakse vahele
  -L, --files-without-match tr�ki ainult failinimed, kus mustrit ei leitud
  -l, --files-with-matches  tr�ki ainult failinimed, kus muster leiti
  -c, --count               tr�ki ainult leitud ridade arv faili kaupa
  -Z, --null                tr�ki peale filinime bait 0
 
Teatage palun vigadest aadressil <bug-grep@gnu.org>.
   -E, --extended-regexp     MUSTER on laiendatud regulaaravaldis
  -F, --fixed-strings       MUSTER on hulk reavahetustega eraldatud s�nesid
  -G, --basic-regexp        MUSTER on lihtne regulaaravaldis
  -P, --perl-regexp         MUSTER on Perl regulaaravaldis
   -e, --regexp=MUSTER       kasuta regulaaravaldisena
  -f, --file=FAIL           loe MUSTER failist FAIL
  -i, --ignore-case         ignoreeri suur- ja v�iket�htede erinevusi
  -w, --word-regexp         kasuta MUSTRIT s�nade leidmiseks
  -x, --line-regexp         kasuta MUSTRIT ridade leidmiseks
  -z, --null-data           andmerida l�ppeb baidil 0, mitte reavahetusel
 %s (GNU grep) %s
 %s: lubamatu v�ti -- %c
 %s: vigane v�ti -- %c
 %s: v�ti `%c%s' ei luba argumenti
 %s: v�ti `%s' on segane
 %s: v�ti `%s' n�uab argumenti
 %s: v�ti `--%s' ei luba argumenti
 %s: v�ti `-W %s' ei luba argumenti
 %s: v�ti `-W %s' on segane
 %s: v�ti n�uab argumenti -- %c
 %s: tundmatu v�ti `%c%s'
 %s: tundmatu v�ti `--%s'
 ' (standardsisend) Kahendfail %s sobib
 Autori�igus 1988, 1992-1999, 2000, 2001 Free Software Foundation, Inc.
 M�lu on otsas S�ntaksit pole m��ratud Otsi MUSTRIT igast FAIList v�i standardsisendist.
N�iteks: %s -i 'tere k�ik' menu.h main.c

Regulaaravaldise valik ja interpreteerimine:
 V�tmeid -P ja -z ei saa koos kasutada V�tit -P ei toetata See on vaba tarkvara; kopeerimistingimused leiate l�htetekstidest. Garantii
PUUDUB; ka m��giks v�i mingil eesm�rgil kasutamiseks, vastavalt seadustega
lubatud piiridele.
 Lisainfo saamiseks proovige v�tit `%s --help'.
 Balanseerimata ( Balanseerimata ) Balanseerimata [ L�petamata \ paojada Tundmatu s�steemi viga Kasuta: %s [V�TI]... MUSTER [FAIL] ...
 Kasuta: %s [V�TI]... MUSTER [FAIL] ...
 ` m��rati konfliktsed otsijad sisend on loendamiseks liiga suur vigane konteksti pikkuse argument vigane maksimum vigane korduste arv m�lu on otsas m�lu on otsas rekursiivne kataloogipuu ts�kkel l�petamata korduste arv tundmatu kahendfailide t��p tundmatu seadmete meetod tundmatu kataloogide meetod hoiatus: %s: %s
 kirjutan v�ljundit 