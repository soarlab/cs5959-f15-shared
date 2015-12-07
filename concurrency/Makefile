all: simple_race simple_mutex

simple_race: simple_race.c
	gcc simple_race.c -lpthread -o simple_race

simple_mutex: simple_mutex.c
	gcc simple_mutex.c -lpthread -o simple_mutex

clean:
	rm -f simple_race simple_mutex

