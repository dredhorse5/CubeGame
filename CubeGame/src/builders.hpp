bool trees(int x, int y, int z) {

	for (int X = (x - 3); X < (x + 3); X++)
		for (int Y = y + 1; Y < (y + 5); Y++)
			for (int Z = (z - 3); Z < (z + 3); Z++)
				if (mass[X][Y][Z] == TREE_OAK)
					return 0;

	for (int X = 0; X < 5; X++)
		for (int Y = 0; Y < 7; Y++)
			for (int Z = 0; Z < 5; Z++) {
				if (tree_mass[Y][X][Z] != 0 and mass[x + X - 2][y + Y + 1][z + Z - 2] == 0)
					mass[x + X - 2][y + Y + 1][z + Z - 2] = tree_mass[Y][X][Z];
			}
	return 1;

}