#!/bin/bash
mkdir Coursework
mkdir -p Coursework/{assignments,reports}
cd Coursework/assignments
echo "This is assignment 1." > assignment1.txt
echo "This is assignment 2." > assignment2.txt
cp assignment1.txt ../reports/
mv assignment2.txt ../reports/renamed_assignment.txt
cd ..
mkdir exams
touch exams/exam{1,2}.txt
cp -r exams assignments/
cp -r exams reports/
rm -r exams
ls -l > directory_info.txt
diff reports/assignment1.txt reports/renamed_assignment.txt > content_comparison.txt