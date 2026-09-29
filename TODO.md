# TODO

## Features:
- Multiple fields ( just take whatever there is in the heading and use that as a summary)
- Images
- Links

## Changes/Fixes:
- Blocks or inlines which are just started and never ended do not count as starting a new one (this could be implemented by testing whether the construct range would be greater than 0 and reworking that function)
- insufficient tests for Parser
- nested emphasis and strong dont really work
- Tests for Cloze inline/Block/Cards
