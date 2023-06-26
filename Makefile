all: thesis presentation

thesis:
	pdflatex main.tex
	bibtex main
	pdflatex main.tex
	pdflatex main.tex

presentation:
	pdflatex presentation.tex

.PHONY=clean
dot_sources= ${shell ls dot}


clean:
	rm -f *.aux *.fdb_latexmk *.fls *.out *.gz *.log *.bbl *.blg *.toc
