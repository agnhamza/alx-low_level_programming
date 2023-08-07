#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define ELF_MAGIC_SIZE 4

typedef struct {
	unsigned char e_ident[ELF_MAGIC_SIZE];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} Elf64_Ehdr;

void print_error(const char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(98);
}

void print_elf_header(const char *filename) {
	int fd = open(filename, O_RDONLY);
	if (fd == -1) {
		print_error("Error opening file");
	}

	Elf64_Ehdr header;
	if (read(fd, &header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
		print_error("Error reading ELF header");
	}

	if (header.e_ident[0] != 0x7F || header.e_ident[1] != 'E' || header.e_ident[2] != 'L' || header.e_ident[3] != 'F') {
		print_error("Not an ELF file");
	}

	printf("Magic: ");
	for (int i = 0; i < ELF_MAGIC_SIZE; ++i) {
		printf("%02x ", header.e_ident[i]);
	}
	printf("\nClass: %u-bit\n", header.e_ident[4] == 1 ? 32 : 64);
	printf("Data: %s endian\n", header.e_ident[5] == 1 ? "little" : "big");
	printf("Version: %u\n", header.e_ident[6]);
	printf("OS/ABI: %u\n", header.e_ident[7]);
	printf("ABI Version: %u\n", header.e_ident[8]);
	printf("Type: %u\n", header.e_type);
	printf("Entry point address: 0x%lx\n", (unsigned long)header.e_entry);

	close(fd);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		print_error("Usage: elf_header elf_filename");
	}

	print_elf_header(argv[1]);

	return 0;
}
