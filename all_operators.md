# All Operators

This file will hold a table for each datatype of this language.

- Each column will be a datatype.
- Each row will be a binary operator.
- Each cell will be the resulting datatype.

## Boolean

|      | Boolean | Integer | Decimal | Character | String |
|:----:|:-------:|:-------:|:-------:|:---------:|:------:|
|  +   | Integer | Integer | Decimal |   n.a.    | String |
|  -   | Integer | Integer | Decimal |   n.a.    |  n.a.  |
|  *   | Integer | Integer | Decimal |   n.a.    |  n.a.  |
|  /   |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
|  <   | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
|  \>  | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
|  <=  | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
| \>=  | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
|  ==  | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
|  !=  | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
|  &&  | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
| \|\| | Boolean |  n.a.   |  n.a.   |   n.a.    |  n.a.  |

## Integer

|      | Boolean | Integer | Decimal | Character | String |
|:----:|:-------:|:-------:|:-------:|:---------:|:------:|
|  +   | Integer | Integer | Decimal |  Integer  | String |
|  -   | Integer | Integer | Decimal |  Integer  |  n.a.  |
|  *   | Integer | Integer | Decimal |  Integer  | String |
|  /   |  n.a.   | Integer | Decimal |  Integer  |  n.a.  |
|  <   |  n.a.   | Boolean | Boolean |  Boolean  |  n.a.  |
|  \>  |  n.a.   | Boolean | Boolean |  Boolean  |  n.a.  |
|  <=  |  n.a.   | Boolean | Boolean |  Boolean  |  n.a.  |
| \>=  |  n.a.   | Boolean | Boolean |  Boolean  |  n.a.  |
|  ==  |  n.a.   | Boolean | Boolean |  Boolean  |  n.a.  |
|  !=  |  n.a.   | Boolean | Boolean |  Boolean  |  n.a.  |
|  &&  |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
| \|\| |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.  |

## Decimal

|      | Boolean | Integer | Decimal | Character | String |
|:----:|:-------:|:-------:|:-------:|:---------:|:------:|
|  +   | Decimal | Decimal | Decimal |   n.a.    | String |
|  -   | Decimal | Decimal | Decimal |   n.a.    |  n.a.  |
|  *   | Decimal | Decimal | Decimal |   n.a.    |  n.a.  |
|  /   |  n.a.   | Decimal | Decimal |   n.a.    |  n.a.  |
|  <   |  n.a.   | Boolean | Boolean |   n.a.    |  n.a.  |
|  \>  |  n.a.   | Boolean | Boolean |   n.a.    |  n.a.  |
|  <=  |  n.a.   | Boolean | Boolean |   n.a.    |  n.a.  |
| \>=  |  n.a.   | Boolean | Boolean |   n.a.    |  n.a.  |
|  ==  |  n.a.   | Boolean | Boolean |   n.a.    |  n.a.  |
|  !=  |  n.a.   | Boolean | Boolean |   n.a.    |  n.a.  |
|  &&  |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
| \|\| |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.  |

## Character

|      | Boolean | Integer | Decimal | Character | String |
|:----:|:-------:|:-------:|:-------:|:---------:|:------:|
|  +   |  n.a.   | Integer |  n.a.   |  Integer  | String |
|  -   |  n.a.   | Integer |  n.a.   |  Integer  |  n.a.  |
|  *   |  n.a.   | Integer |  n.a.   |  Integer  |  n.a.  |
|  /   |  n.a.   | Integer |  n.a.   |  Integer  |  n.a.  |
|  <   |  n.a.   |  n.a.   |  n.a.   |  Boolean  |  n.a.  |
|  \>  |  n.a.   |  n.a.   |  n.a.   |  Boolean  |  n.a.  |
|  <=  |  n.a.   |  n.a.   |  n.a.   |  Boolean  |  n.a.  |
| \>=  |  n.a.   |  n.a.   |  n.a.   |  Boolean  |  n.a.  |
|  ==  |  n.a.   |  n.a.   |  n.a.   |  Boolean  |  n.a.  |
|  !=  |  n.a.   |  n.a.   |  n.a.   |  Boolean  |  n.a.  |
|  &&  |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.  |
| \|\| |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.  |

## String

|      | Boolean | Integer | Decimal | Character | String  |
|:----:|:-------:|:-------:|:-------:|:---------:|:-------:|
|  +   | String  | String  | String  |  String   | String  |
|  -   |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.   |
|  *   |  n.a.   | String  |  n.a.   |   n.a.    |  n.a.   |
|  /   |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.   |
|  <   |  n.a.   |  n.a.   |  n.a.   |   n.a.    | Boolean |
|  \>  |  n.a.   |  n.a.   |  n.a.   |   n.a.    | Boolean |
|  <=  |  n.a.   |  n.a.   |  n.a.   |   n.a.    | Boolean |
| \>=  |  n.a.   |  n.a.   |  n.a.   |   n.a.    | Boolean |
|  ==  |  n.a.   |  n.a.   |  n.a.   |   n.a.    | Boolean |
|  !=  |  n.a.   |  n.a.   |  n.a.   |   n.a.    | Boolean |
|  &&  |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.   |
| \|\| |  n.a.   |  n.a.   |  n.a.   |   n.a.    |  n.a.   |