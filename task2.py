import json
from random import randint


class Word:
    def __init__(self, main_word: str, subwords: list):
        self.main_word = main_word
        self.subwords = subwords

    def check_word(self, word: str) -> bool:
        if word in self.subwords:
            return True
        return False

    def count_words(self) -> int:
        return len(self.subwords)


class Player:
    def __init__(self, username):
        self.username = username
        self.used_words = []

    def get_used_words(self) -> int:
        return len(self.used_words)

    def add_word(self, word: str) -> None:
        self.used_words.append(word)

    def check_word_is_new(self, word: str) -> bool:
        if word in self.used_words:
            return False
        return True


def load_words(json_data: str) -> list:
    words = []
    raw_words = json.loads(json_data)
    for raw_word in raw_words:
        main_word = raw_word['word']
        subwords = raw_word['subwords']
        words.append(Word(main_word, subwords))
    return words


def load_random_word(words: list) -> Word:
    return words[randint(0, len(words) - 1)]


def main():
    # load words
    with open("words.json", "r") as f:
        words = load_words(f.read())
    # select random word
    original_word = load_random_word(words)
    subwords_count = original_word.count_words()
    # initialize player
    username = input("Введите имя игрока: ")
    player = Player(username)
    # print game info
    print(f"Привет, {username}")
    print(f"Составте слова из букв слова {original_word.main_word.upper()}")
    print(f"Слова должны быть не короче 3 букв")
    print(f'Чтобы закончить игру, напишите "stop"')
    # start game
    while player.get_used_words() < subwords_count:
        word = input('Введите слово: ').lower()
        if word == 'stop':
            break
        if len(word) < 3:
            print('Слова должны быть не короче 3 букв')
            continue
        if original_word.check_word(word) and player.check_word_is_new(word):
            print('Верно')
            player.add_word(word)
        else:
            print('Неверно')
    # print game results
    print(f"Игра завершена, вы угадали {player.get_used_words()} слов(а) из {subwords_count}")
    print(f"Использованные слова: {', '.join(player.used_words)}")


if __name__ == "__main__":
    main()
