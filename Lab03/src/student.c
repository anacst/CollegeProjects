
typedef struct {
	char name[16];
	char surname[16];
	char course[32];
	int nusp;
	float grade;
} tStudent;

void createStudent() {
	printf("\n\t\tCADASTRO\n\n");
	printf("\tNº usp do aluno: ");
	scanf("%d", &student.nusp);
	printf("\tNome do aluno: ");
	scanf(" %[^\n]s%*c", student.name);
	printf("\tSobrenome do aluno: ");
	scanf(" %[^\n]s%*c", student.surname);
	printf("\tCurso do aluno: ");
	scanf(" %[^\n]s%*c", student.course);
	printf("\tNota do aluno: ");
	scanf("%f", &student.grade);
}

void printStudent() {
	printf("\n\tInformações do aluno\n\n");
	printf("\tNº usp do aluno: %d\n", student->nusp);
	printf("\tNome do aluno: %s\n", student->name);
	printf("\tSobrenome do aluno: %s\n", student->surname);
	printf("\tCurso do aluno: %s\n", student->course);
	printf("\tNota do aluno: %.2f\n", student->grade);

}
