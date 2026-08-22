
auto markdown_to_html(std::string markdown) -> std::string;

auto render_field(std::vector<Block> blocks) -> std::string;
auto render_block(Block block) -> std::string;
