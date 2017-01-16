# Information Retrieval 101

[![Join the chat at https://gitter.im/information-retrieval-101/Lobby](https://badges.gitter.im/information-retrieval-101/Lobby.svg)](https://gitter.im/information-retrieval-101/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Information Retrieval (aka web scraping) is the process of collecting information from a network resource. This document is a (WIP) introduction to differenct aspects and techniques involved in an information retrival system.

Most of this text will be language-agnostic, but code snippets will probably break that rule.

## The Process
You can crudely break down any IR process into 3 steps:

* acquiring or requesting a network resource
* parsing the payload
* transformation and storage

There is also a 4th step that's concerned with finding _what_ to reterieve, but we'll come to that later.

systematic resources are generally easier to reterieve compared to non-systematic resources. What are systematic resources you ask? systematic resources are network resources that have a _pattern_ to them. One good example of a systematic resource is a infinitely scrolling webpage. You know that as long as you keep scrolling down you'll keep getting more content loaded, therefore it has a repeatable behaviour that you can rely on.

let's now walk through the IR process, step by step

### Step 1: acquiring or requesting a network resource
This should be self-explainatory. If you want to scrape data from a news website, you begin by first loading the contents of that webpage.

### Step 2: parsing the payload
Once you have loaded a resource, the next logical step is to parse the resource data. Most of the time you'll be extracting data from a structured interchange langauge (XML, HTML, JSON et al). These representations make it exceedingly easy to extract and query data from them. Scraping data from non-structured text requires some arcane invocations that are beyond the scope of this text.

### Step 3: transformation and storage
This stage involves making changes to the extracted data so it fits your use case. It can range from simple pipelines that save some extracted data as is, to all sorts of sequential or concurrent transformations.

have some pseudo code:
```
resource = request('/resource/url')
data = parse(resource).extract('data')
save(data)
```

## An Example

Let's start off with a very simple program that scrapes some data off hacker news. To keep it simple, we'll only be extracting the title of the posts that appear on the first page of hacker news.

```python
# -*- coding: utf-8 -*-

'''
    fetch the title of the latest posts on page 1 of hacker news

    because who doesn't like hackers news?
'''

import requests
import lxml.etree

URL = 'http://news.ycombinator.com'

# fetch the page
response = requests.get(URL)

# parse the page
document = lxml.etree.HTML(response.text)

# on inspecting the HTML of the document, you'll see that every HN
# post has an anchor tag with the class 'story' inside a table row
# with a class 'athing'. We use the cssselect library in order to
# select all those elements that match this description. The result is a 
# list of lxml.etree.Element objects.
#
# you can also use xpath to select elements, for example:
# document.xpath("//tr[@class='athing']//a[@class='storylink']"):
# selects the same elements as the css expression 'tr.athing a.storylink'

for title in document.cssselect('tr.athing a.storylink'):
    print(title.text)
```



