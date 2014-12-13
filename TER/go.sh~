if [[ $1 == *compile* ]]
then
	echo "Lancement du makefile , puis execution"
	make remove
	make
	#mpirun -n 4 ./bin/GUI_SDL.exe ./props/config.props ./props/proprietes.props
	echo "Compilation terminee correctement !"
	exit
fi

if [[ $1 == *exec* ]]
then
	mpirun -n 4  ./bin/GUI_SDL.exe ./props/config.props ./props/proprietes.props
	echo "Execution terminee resultats dans le dossier results et logs dans le dossier logs"
fi
