#!/usr/bin/env zsh
# https://stackoverflow.com/a/19648328
ulimit -s unlimited

set -o errexit

if [[ "$#" != 1 ]]; then
    echo "Usage: $0 CONTEST_NAME"
    exit 1
fi

contest_name=$1
if [[ ! -d "$contest_name" ]]; then
    echo "Contest '$contest_name' does not exists."
    exit 1
fi

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $contest_name

RELEASE='release'

mkdir -p $RELEASE

STATEMENT=$RELEASE/statement.md
echo '' > $STATEMENT

COVER_TOC=$RELEASE/cover.toc.tex
{
  echo '\\begin{tabular}{cl}'
  echo '\\toprule'
} > $COVER_TOC

problem_count=64
for problem in $(cat PROBLEMS); do
    problem_count=$(($problem_count + 1))
    code=$(echo $problem_count | awk '{printf("%c", $1)}')

    (cd $problem && rake -m)

    $SCRIPT_DIR/pack4dj.py $problem $RELEASE/$code.zip

    title=$(egrep '^# ' $problem/statement.md | sed -e 's/# //g')
    echo "${code} & ${title} \\\\\\\\" >> $COVER_TOC

    cat $problem/statement.md >> $STATEMENT
    {
        printf "\n## Sample Input\n\`\`\`\n"
        cat $problem/samples/???
        printf "\`\`\`\n\n## Sample Output\n\`\`\`\n"
        cat $problem/samples/???.a
        printf "\`\`\`\n\n"
    } | python -c "import sys; sys.stdout.write(open('$STATEMENT').read().replace('<!--SAMPLES-->', sys.stdin.read()))" > $STATEMENT.new
    mv $STATEMENT.new $STATEMENT

    printf "\n\\\newpage\n\n" >> $STATEMENT
done

{
  echo '\\bottomrule'
  echo '\\end{tabular}'
} >> $COVER_TOC

cp $SCRIPT_DIR/{ccpc.png,bupt.png} $RELEASE
if [[ $contest_name == "main" ]]; then
  cat $SCRIPT_DIR/cover.tex | sed -e "s/REVNUM/$(git rev-parse --short HEAD)/g" > $RELEASE/cover.tex
fi
if [[ $contest_name == "warmup" ]]; then
  cat $SCRIPT_DIR/cover.tex | sed -e 's/30th/20th/g' -e 's/Contest Session/Practice Session/g' -e "s/REVNUM/$(git rev-parse --short HEAD)/g" > $RELEASE/cover.tex
fi
(cd $RELEASE && xelatex cover.tex && find . -name cover\* -not -name cover.pdf -delete && rm -rf *.png)

pandoc $STATEMENT --latex-engine=xelatex --template=$SCRIPT_DIR/template.tex -o"$RELEASE/statement.pdf" \
|| pandoc $STATEMENT --pdf-engine=xelatex --template=$SCRIPT_DIR/template.tex -o"$RELEASE/statement.pdf"

if command -v pdftk &> /dev/null; then
  pdftk $RELEASE/cover.pdf $RELEASE/statement.pdf cat output $RELEASE/${contest_name}.$(git rev-parse --short HEAD).pdf
fi

cd -
