#!/usr/bin/env fish

set -l dirs (fd --type d --max-depth 1)
echo "Found "(count $dirs)" subdirs"
for dir in $dirs
    echo ""
    echo ""
    echo ""
    echo "==> $dir/"
    pushd $dir >/dev/null

    set -l exe ./a.out

    if test -e Makefile; or test -e makefile
        # Only run 'make clean' if the target exists
        if make -n clean >/dev/null ^/dev/null
            make clean ^/dev/null
        end

        if not make
            echo "Build failed in $dir/"
            popd >/dev/null
            continue
        end
    end

    if test -x $exe
        echo "-- Running $exe"
        $exe
        echo "-- Exit status: $status"
    else
        echo "No executable found in $dir/ (expected $exe)."
    end

    popd >/dev/null
end
