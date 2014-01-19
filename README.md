KontoCheck
===========

make targets
-------------

Build the demo executable (includes lut-tools)

    make konto_check

Build the test-only demo

    make konto_check_mini

Test bankaccounts in file `testkonten.txt`

    echo "12345678 0001112223" >> testkonten.txt
    make test

Recreate `.lut2` database from
[Bundesbank](http://www.bundesbank.de/Redaktion/DE/Standardartikel/Kerngeschaeftsfelder/Unbarer_Zahlungsverkehr/bankleitzahlen_download.html)
input

    make lut

---------------------------------------------------------

 * TODO: Build on Linux
 * TODO: Use CGO

---------------------------------------------------------

This projected is licensed under the terms of the GNU Lesser General Public License.
