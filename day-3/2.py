from pathlib import Path
import re

Pairs = list[str]


def main() -> None:
    reg_muls: Pairs = []
    cond_muls: Pairs = []

    try:
        with open("input.txt", "r") as raw_file:
            contents = raw_file.read()
            reg_muls = findall_muleqs(contents)
            cond_muls = findall_muleqs(contents, conditional=True)

        prod_sum_reg = sum_pair_products(reg_muls)
        prod_sum_cond = sum_pair_products(cond_muls)

        print(prod_sum_reg)
        print(prod_sum_cond)

    except FileNotFoundError as e:
        print(f"{e}")


def findall_muleqs(contents, conditional=False) -> Pairs:
    patterns = {
        "regular": r"mul\(\d{1,3}\,\d{1,3}\)",
        "enabled": r"(do\(\)|don\'t\(\)|mul\(\d{1,3},\d{1,3}\))",
    }
    cleaned_items = []

    if not conditional:
        cleaned_items = re.findall(patterns["regular"], contents)
    else:
        matches = [m.group() for m in re.finditer(patterns["enabled"], contents)]
        enabled = True

        for match in matches:
            match match:
                case "do()":
                    enabled = True
                case "don't()":
                    enabled = False
                case _ if match.startswith("mul"):
                    cleaned_items.append(match) if enabled else None

    return cleaned_items


def sum_pair_products(clean_pairs: Pairs) -> int:
    str_pairs: list[Pairs] = [
        item.replace("mul(", "").replace(")", "").split(",") for item in clean_pairs
    ]
    product_sum = sum([int(pair[0]) * int(pair[1]) for pair in str_pairs])
    return product_sum


if __name__ == "__main__":
    main()