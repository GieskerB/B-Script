# All Operators

This file will hold a table for each datatype of this language.

- Each column will be a datatype.
- Each row will be a binary operator.
- Each cell will be the resulting datatype.

## Boolean

|      | Boolean | Integer | Decimal | String |
|:----:|:-------:|:-------:|:-------:|:------:|
|  +   | Integer | Integer | Decimal | String |
|  -   | Integer | Integer | Decimal |  n.a.  |
|  *   | Integer | Integer | Decimal |  n.a.  |
|  /   |  n.a.   |  n.a.   |  n.a.   |  n.a.  |
|  <   | Boolean |  n.a.   |  n.a.   |  n.a.  |
|  \>  | Boolean |  n.a.   |  n.a.   |  n.a.  |
|  <=  | Boolean |  n.a.   |  n.a.   |  n.a.  |
| \>=  | Boolean |  n.a.   |  n.a.   |  n.a.  |
|  ==  | Boolean |  n.a.   |  n.a.   |  n.a.  |
|  !=  | Boolean |  n.a.   |  n.a.   |  n.a.  |
|  &&  | Boolean |  n.a.   |  n.a.   |  n.a.  |
| \|\| | Boolean |  n.a.   |  n.a.   |  n.a.  |

## Integer

|      | Boolean | Integer | Decimal | String |
|:----:|:-------:|:-------:|:-------:|:------:|
|  +   | Integer | Integer | Decimal | String |
|  -   | Integer | Integer | Decimal |  n.a.  |
|  *   | Integer | Integer | Decimal | String |
|  /   |  n.a.   | Integer | Decimal |  n.a.  |
|  <   |  n.a.   | Boolean | Boolean |  n.a.  |
|  \>  |  n.a.   | Boolean | Boolean |  n.a.  |
|  <=  |  n.a.   | Boolean | Boolean |  n.a.  |
| \>=  |  n.a.   | Boolean | Boolean |  n.a.  |
|  ==  |  n.a.   | Boolean | Boolean |  n.a.  |
|  !=  |  n.a.   | Boolean | Boolean |  n.a.  |
|  &&  |  n.a.   |  n.a.   |  n.a.   |  n.a.  |
| \|\| |  n.a.   |  n.a.   |  n.a.   |  n.a.  |

## Decimal

|      | Boolean | Integer | Decimal | String |
|:----:|:-------:|:-------:|:-------:|:------:|
|  +   | Decimal | Decimal | Decimal | String |
|  -   | Decimal | Decimal | Decimal |  n.a.  |
|  *   | Decimal | Decimal | Decimal |  n.a.  |
|  /   |  n.a.   | Decimal | Decimal |  n.a.  |
|  <   |  n.a.   | Boolean | Boolean |  n.a.  |
|  \>  |  n.a.   | Boolean | Boolean |  n.a.  |
|  <=  |  n.a.   | Boolean | Boolean |  n.a.  |
| \>=  |  n.a.   | Boolean | Boolean |  n.a.  |
|  ==  |  n.a.   | Boolean | Boolean |  n.a.  |
|  !=  |  n.a.   | Boolean | Boolean |  n.a.  |
|  &&  |  n.a.   |  n.a.   |  n.a.   |  n.a.  |
| \|\| |  n.a.   |  n.a.   |  n.a.   |  n.a.  |

## String

|      | Boolean | Integer | Decimal | String  |
|:----:|:-------:|:-------:|:-------:|:-------:|
|  +   | String  | String  | String  | String  |
|  -   |  n.a.   |  n.a.   |  n.a.   |  n.a.   |
|  *   |  n.a.   | String  |  n.a.   |  n.a.   |
|  /   |  n.a.   |  n.a.   |  n.a.   |  n.a.   |
|  <   |  n.a.   |  n.a.   |  n.a.   | Boolean |
|  \>  |  n.a.   |  n.a.   |  n.a.   | Boolean |
|  <=  |  n.a.   |  n.a.   |  n.a.   | Boolean |
| \>=  |  n.a.   |  n.a.   |  n.a.   | Boolean |
|  ==  |  n.a.   |  n.a.   |  n.a.   | Boolean |
|  !=  |  n.a.   |  n.a.   |  n.a.   | Boolean |
|  &&  |  n.a.   |  n.a.   |  n.a.   |  n.a.   |
| \|\| |  n.a.   |  n.a.   |  n.a.   |  n.a.   |