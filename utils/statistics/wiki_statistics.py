import re
import enum
import typing
import logging
import statistics
import numpy

from multiprocessing.dummy import Pool

import numpy as np
import pylab

TREADS_COUNT = 3
DOC_BEGIN_RE = r'<doc id="(.*)" url="(.*)" title="(.*)">'
DOC_END_RE = r'</doc>'


class Statistics:
    def __init__(self):
        self.doc_length = []


class ParsingState(enum.Enum):
    DOC_BEGIN = 0
    DOC_CONTENT = 1
    DOC_END = 2


def process_all(batch_filenames: typing.List[str]) -> Statistics:
    pool = Pool(TREADS_COUNT)
    results = pool.map(process_batch, batch_filenames)
    aggregated_results = aggregate(results)
    return aggregated_results


def process_batch(batch_filename: str) -> Statistics:
    result = Statistics()
    with open(batch_filename, 'r') as fo:
        state = ParsingState.DOC_BEGIN
        doc = ""
        for line in fo:
            if re.search(DOC_BEGIN_RE, line) and state == ParsingState.DOC_BEGIN:
                state = ParsingState.DOC_CONTENT
                result.doc_length.append(len(doc))
                doc = ""
            elif re.search(DOC_END_RE, line):
                state = ParsingState.DOC_BEGIN
            elif state == ParsingState.DOC_CONTENT:
                doc += line
    return result


def aggregate(statistics_list: typing.List[Statistics]) -> Statistics:
    result = Statistics()
    for statistics_item in statistics_list:
        result.doc_length.extend(statistics_item.doc_length)
    return result


def draw(stats: Statistics) -> None:
    pylab.hist(stats.doc_length, bins=[2 * i for i in range(250)], density=True)
    pylab.grid()
    pylab.xlabel('Docs length')
    pylab.ylabel('Density')
    pylab.show()


def main() -> None:
    batch_filenames = [
        '/home/just3mhz/IR/parsed_wiki/wiki_01',
        '/home/just3mhz/IR/parsed_wiki/wiki_02',
        '/home/just3mhz/IR/parsed_wiki/wiki_03',
        '/home/just3mhz/IR/parsed_wiki/wiki_04'
    ]
    result = process_all(batch_filenames)
    print("Mean: ", statistics.mean(result.doc_length))
    print("Median: ", statistics.median(result.doc_length))
    print("Mode: ", statistics.mode(result.doc_length))
    draw(result)


if __name__ == '__main__':
    main()
